#ifndef KPROTOCOLLINERECEIVER_H
#define KPROTOCOLLINERECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QSslSocket>

// TODO : handle network failures

class KProtocolLineReceiver : public QObject
{
    Q_OBJECT
public:
    explicit KProtocolLineReceiver(QObject *parent = 0);
	bool connectToLineHost(QString host, quint16 port = 0x666, bool secure = true);
	void disconnectFromLineHost();

	static const qint64 MaxLineLength = 16384;

signals:
	void lineReceived(QString line);

public slots:
	void sendLine(QString line);

private:
	QTcpSocket *s_;
	QString host_;
	quint16 port_;
	bool secure_;

	QString cur_line_;

private slots:
	void incomingData();
};

#endif // KPROTOCOLLINERECEIVER_H
