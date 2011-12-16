#include "kommunikator.h"

#include <QDebug>

Kommunikator::Kommunikator(QObject *parent) :
	QObject(parent), seq_(0), ks_(Unestablished)
{
	connect(&jsr_, SIGNAL(jsonReceived(QVariant)), this, SLOT(handleIncoming(QVariant)));
}

void Kommunikator::handleIncoming(QVariant json) {
	QVariantMap m = json.toMap();

	// TODO dans le futur il faudra gérer le fait que le serveur puisse lui aussi
	// initier des communications.

	if(!m.contains("seq")) {
		emit invalidMessage(json);
		return;
	}

	if(m["action"].toString() == "error") {
		emit gotError(m["seq"].toInt(), m["code"].toInt(), m["name"].toString());
		return;
	}

	emit gotReply(m["seq"].toInt(), json);
}

bool Kommunikator::konnect(QString host, quint16 port, bool secure) {
	if(!jsr_.connectToLineHost(host, port, secure)) {
		return false;
	}

	KweryInit *kw = new KweryInit;
	connect(kw, SIGNAL(done()), this, SLOT(initDone()));
	connect(kw, SIGNAL(error(int,QString)), this, SLOT(initFailed(int,QString)));
	sendKwery(kw);
}

void Kommunikator::sendKwery(Kwery *kw) {
	connect(this, SIGNAL(gotReply(int,QVariant)), kw, SLOT(handleReply(int,QVariant)));
	connect(this, SIGNAL(gotError(int,int,QString)), kw, SLOT(handleError(int,int,QString)));
	kw->seq_ = ++seq_;

	jsr_.sendJson(kw->makeMessage());
}

void Kommunikator::authCheckout(int id) {
	// TODO do real auth
	KweryAuthCheckout *kw = new KweryAuthCheckout(id);
	connect(kw, SIGNAL(authSuccess()), this, SLOT(authSuccess()));
	connect(kw, SIGNAL(authFail()), this, SLOT(authFailed()));
	sendKwery(kw);
}

void Kommunikator::setState(KonnState state) {
	ks_ = state;
	emit stateChanged(state);
}

void Kommunikator::initDone() {
	setState(Established);
}

void Kommunikator::initFailed(int,QString) {
	setState(Unestablished);
}

void Kommunikator::authFailed() {
	// TODO display proper warning
	qDebug() << "Authentication failed";
}

void Kommunikator::authSuccess() {
	qDebug() << "Authentication successful";
	setState(Authenticated);
}
