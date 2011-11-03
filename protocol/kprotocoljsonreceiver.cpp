#include "kprotocoljsonreceiver.h"

#include <QBuffer>

KProtocolJsonReceiver::KProtocolJsonReceiver(QObject *parent) :
    KProtocolLineReceiver(parent)
{
	connect(this, SIGNAL(lineReceived(QString)), this, SLOT(incomingLine(QString)));
}

void KProtocolJsonReceiver::incomingLine(QString line) {
	bool ok;
	QVariant data;
	QJson::Parser parser;

	data = parser.parse(line.toUtf8(), &ok);

	if(ok) {
		emit jsonReceived(data);
	}
}

void KProtocolJsonReceiver::sendJson(QVariant data) {
	QJson::Serializer serializer;

	this->sendLine(QString::fromAscii(serializer.serialize(data)));
}
