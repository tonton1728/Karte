#include <QtCore/QCoreApplication>
#include <QString>
#include <QDebug>

#include "kommunikator.h"
#include "kwery.h"

/*class Receiver : public QObject {
	Q_OBJECT

public slots:
	void displayLine(QString line) {
		qDebug() << line;
	}

	void displayJson(QVariant js) {
		qDebug() << js;
	}
};*/

class KomTest : public QObject {
	Q_OBJECT

private:
	Kommunikator kom;
	enum State {
		Idle, Connecting, Authenticating
	};
	State s;

public:
	KomTest() : s(Idle) {
		connect(&kom, SIGNAL(stateChanged(Kommunikator::KonnState)), this, SLOT(komStateChange(Kommunikator::KonnState)));

		setState(Connecting);
	}

private:
	void setState(State s) {
		this->s = s;

		switch(s) {
		case Connecting:
			kom.konnect("loc.telnet-tl1.org", 8000, false);
			break;
		case Authenticating:
			kom.authCheckout(42);
			break;
		default:
			/* prison */ break;
		}
	}

private slots:
	void komStateChange(Kommunikator::KonnState st) {
		qDebug() << "New Kom State:" << st;

		if(st == Kommunikator::Established) {
			if(s == Connecting) {
				setState(Authenticating);
			}
		}
	}


};

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);
	/*Receiver r;
	KProtocolJsonReceiver p;*/

	/*QObject::connect(&p, SIGNAL(jsonReceived(QVariant)), &r, SLOT(displayJson(QVariant)));
	QObject::connect(&p, SIGNAL(lineReceived(QString)), &r, SLOT(displayLine(QString)));

	p.connectToLineHost("loc.telnet-tl1.org", 8000, false);

	QVariantMap init;
	init["action"] = "init";
	init["version"] = 1;
	init["seq"] = 1;

	p.sendJson(init);

	QVariantMap authCo;
	authCo["action"] = "auth-checkout";
	authCo["seq"] = 2;
	authCo["checkout_id"] = 42;

	p.sendJson(authCo);*/

	KomTest test;

	return app.exec();
}

#include "test_karte.moc"
