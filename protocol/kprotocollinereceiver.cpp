#include "kprotocollinereceiver.h"

#include <QHostInfo>
#include <QFile>
#include <QDebug>
#include <algorithm>

KProtocolLineReceiver::KProtocolLineReceiver(QObject *parent) :
QObject(parent), s_(0), cur_line_("")
{
}

bool KProtocolLineReceiver::connectToLineHost(QString host, quint16 port, bool secure) {
	if(s_ != 0) if(s_->state() != QAbstractSocket::UnconnectedState) {
		return false;
	}

	host_ = host;
	port_ = port;
	secure_ = secure;

	if(secure_) {
		QFile f(":/ssl/cacert.pem");
		f.open(QFile::ReadOnly);

		QSslCertificate cert(&f);

		QSslSocket *s = new QSslSocket(this);
		s->addCaCertificate(cert);

		s->connectToHostEncrypted(host_, port_, QIODevice::ReadWrite);
		if(!s->waitForEncrypted()) {
			delete s;
			return false;
		}

		s_ = s;
	} else {
		QTcpSocket *s = new QTcpSocket(this);
		s->connectToHost(host_, port_, QIODevice::ReadWrite);
		if(!s->waitForConnected()) {
			delete s;
			return false;
		}

		s_ = s;
	}

	connect(s_, SIGNAL(readyRead()), this, SLOT(incomingData()));

	return true;
}

void KProtocolLineReceiver::incomingData() {
	QByteArray buf;

	qDebug() << "got incoming data";

	buf = s_->read(MaxLineLength);

	int pos = 0, oldpos = -1;
	while((pos = buf.indexOf('\n', oldpos + 1)) != -1) {
		qint64 seglen = pos - oldpos - 1;

		if(cur_line_.length() + seglen > MaxLineLength) {
			// Line is too big, do nothing
		} else {
			cur_line_ += QString::fromUtf8(buf.mid(oldpos + 1, seglen));
			emit lineReceived(cur_line_);
			cur_line_ = QString();
		}

		oldpos = pos;
	}
}

void KProtocolLineReceiver::disconnectFromLineHost() {
	s_->disconnectFromHost();
}

void KProtocolLineReceiver::sendLine(QString line) {
	s_->write(line.toAscii() + '\n');
}
