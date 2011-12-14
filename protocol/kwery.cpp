#include "kwery.h"

//
// Base Kwery
//

Kwery::Kwery(QObject *parent) :
	QObject(parent), seq_(-1)
{
}

void Kwery::handleReply(int seq, const QVariant json) {
	if(seq == seq_) {
		this->handleReply(json);
		this->deleteLater();
	}
}

void Kwery::handleError(int seq, const int code, const QString name) {
	if(seq == seq_) {
		this->handleError(code, name);
		this->deleteLater();
	}
}

QString Kwery::actionToString(KweryAction act) {
	static QString match[] = {
		"init", "debit", "credit", "auth-checkout", "model-get",
		"model-check-more-data", "model-get-more-data",
		"model-filter", "model-headers"
	};

	return match[act];
}

QVariant Kwery::makeMessage() {
	QVariantMap msg;

	msg["action"] = actionToString(act_);
	msg["seq"] = seq_;
	msg.unite(payload_);

	return msg;
}

void Kwery::handleError(const int code, const QString name) {
	emit error(code, name);
}

//
// KweryInit
//

KweryInit::KweryInit() : Kwery()
{
	act_ = Init;
	payload_["version"] = 1;
}

void KweryInit::handleReply(const QVariant json) {
	emit done();
}

//
// KweryAuthCheckout
//

KweryAuthCheckout::KweryAuthCheckout(int id) : Kwery() {
	act_ = AuthCheckout;
	payload_["checkout_id"] = id;
}

void KweryAuthCheckout::handleReply(const QVariant json) {
	QVariantMap map = json.toMap();

	if(map["allowed"].toBool()) {
		emit authSuccess();
	} else {
		emit authFail();
	}
}
