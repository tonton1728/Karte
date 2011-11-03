#ifndef KPROTOCOLJSONRECEIVER_H
#define KPROTOCOLJSONRECEIVER_H

#include <QObject>
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "kprotocollinereceiver.h"

class KProtocolJsonReceiver : public KProtocolLineReceiver
{
    Q_OBJECT
public:
    explicit KProtocolJsonReceiver(QObject *parent = 0);

signals:
	void jsonReceived(QVariant json);

public slots:
	void sendJson(QVariant data);

private slots:
	void incomingLine(QString line);
};

#endif // KPROTOCOLJSONRECEIVER_H
