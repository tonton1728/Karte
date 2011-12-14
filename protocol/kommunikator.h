#ifndef KOMMUNIKATOR_H
#define KOMMUNIKATOR_H

#include <QObject>

#include "kprotocoljsonreceiver.h"
#include "kwery.h"

// Needed in order to be friend
class Kwery;

class Kommunikator : public QObject
{
    Q_OBJECT
public:
    explicit Kommunikator(QObject *parent = 0);

	bool konnect(QString host, quint16 port = 0x666, bool secure = true);
	void sendKwery(Kwery *kw);
	void authCheckout(int id);

	enum KonnState {
		Unestablished, Established, Authenticated
	};

signals:
	void gotReply(int seq, QVariant json);
	void gotError(int seq, int code, QString name);
	void invalidMessage(QVariant json);
	void stateChanged(Kommunikator::KonnState state);

public slots:
	void handleIncoming(QVariant json);

private slots:
	void setState(KonnState state);
	void initDone();
	void initFailed(int,QString);
	void authSuccess();
	void authFailed();

private:
	KProtocolJsonReceiver jsr_;
	int seq_;
	KonnState ks_;
};

#endif // KOMMUNIKATOR_H
