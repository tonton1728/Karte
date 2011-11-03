#ifndef KPROTOCOLLINETEST_H
#define KPROTOCOLLINETEST_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QTcpSocket>
#include <QStringList>

class KProtocolLineTest : public QThread
{
    Q_OBJECT
public:
    explicit KProtocolLineTest(QObject *parent = 0);

	void init();
	void run();

	QStringList received;

private:
	QTcpSocket s;

signals:

public slots:

};

#endif // KPROTOCOLLINETEST_H
