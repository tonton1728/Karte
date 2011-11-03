#include <QtCore/QCoreApplication>
#include <QString>

#include "kprotocoljsonreceiver.h"

class Receiver : public QObject {
	Q_OBJECT

public slots:
	void displayLine(QString line) {
		qDebug() << line;
	}

	void displayJson(QVariant js) {
		qDebug() << js;
	}
};

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);
	Receiver r;
	KProtocolJsonReceiver p;

	QObject::connect(&p, SIGNAL(jsonReceived(QVariant)), &r, SLOT(displayJson(QVariant)));
	QObject::connect(&p, SIGNAL(lineReceived(QString)), &r, SLOT(displayLine(QString)));

	p.connectToLineHost("loc.telnet-tl1.org", 8000, false);

	QVariantList vl;
	vl << "Coucou !" << 42 << 42.0 << "MA BITE EN 3D" << QString::fromUtf8("ÉLÉPHANT");
	p.sendJson(vl);

	return app.exec();
}

#include "test_karte.moc"
