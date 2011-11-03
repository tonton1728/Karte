#include <QtTest/QtTest>
#include <QObject>
#include <QEventLoop>
#include <QDebug>
#include "kprotocollinereceiver.h"

class KarteTestSlots : public QObject {
	Q_OBJECT

signals:
	void done();

public slots:
	void receiveLine(QString line);

public:
	QList<QVariant> out;
};

class KarteTest : public QObject {
	Q_OBJECT

private slots:
	void connectRemoteHost();
};

void KarteTest::connectRemoteHost() {
	KProtocolLineReceiver kp;
	KarteTestSlots ts;
	QEventLoop loop;

	connect(&kp, SIGNAL(lineReceived(QString)), &ts, SLOT(receiveLine(QString)));
	connect(&ts, SIGNAL(done()), &loop, SLOT(quit()));

	kp.connectToLineHost("loc.telnet-tl1.org", 8000, false);

	loop.exec();

	QCOMPARE(ts.out[0].toString(), QString("salut"));
	QCOMPARE(ts.out[1].toString(), QString("pouet"));
	QCOMPARE(ts.out[2].toString(), QString("j'aime faire caca"));
	QCOMPARE(ts.out[3].toString(), QString::fromUtf8("les éléphants se trompent"));
	QCOMPARE(ts.out[4].toString(), QString("ma bite"));
}

void KarteTestSlots::receiveLine(QString line) {
	static int n = 0;
	out.append(line);

	if(++n == 5)
		emit done();
}

QTEST_MAIN(KarteTest)
#include "main_test.moc";
