#include "kwery.h"

//
// Base Kwery
//

/**
  La classe Kwery sert à représenter une requête émise vers le serveur
  et à gérer la réponse. La classe de base fournit un certain nombre de
  facilités pour minimiser le traval d'implémentation des sous classes :
  globalement une sous-classe n'a besoin de n'implémenter que
  handleReply() et éventuellement handleError().

  Toutes les classes suivant celle-ci sont des sous-classes de Kwery
  servant à représenter les différentes actions du protocole.
  */

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

QString Kwery::actionToString() {
	static QString match[] = {
		"init", "debit", "credit", "auth-checkout", "model-get", "model-data",
		"model-check-more-data", "model-get-more-data",
		"model-filter", "model-headers"
	};

	return match[act_];
}

QVariant Kwery::makeMessage() {
	QVariantMap msg;

	msg["action"] = actionToString();
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

//
// KweryModelGet
//

KweryModelGet::KweryModelGet(QString name) : Kwery(), name(name) {
	act_ = ModelGet;
}

QString KweryModelGet::actionToString() {
	return "model-get " + name;
}

void KweryModelGet::handleReply(const QVariant json) {
	emit gotModel(json.toMap()["model-id"].toInt());
}

//
// KweryModelData
//

KweryModelData::KweryModelData(int mid) : Kwery() {
	act_ = ModelData;
	payload_["model-id"] = mid;
}

void KweryModelData::handleReply(const QVariant json) {
	emit gotData(json.toMap()["data"].toList());
}

//
// KweryModelHeader
//

KweryModelHeaders::KweryModelHeaders(int mid) : Kwery() {
	act_ = ModelHeaders;
	payload_["model-id"] = mid;
}

void KweryModelHeaders::handleReply(const QVariant json) {
	emit gotHeaders(json.toMap()["data"].toList());
}

//
// KweryModelCheckMoreData
//

KweryModelCheckMoreData::KweryModelCheckMoreData(int mid) : Kwery() {
	act_ = ModelCheckMoreData;
	payload_["model-id"] = mid;
}

void KweryModelCheckMoreData::handleReply(const QVariant json) {
	emit moreDataAvailable(json.toMap()["has_more_data"].toBool());
}

//
// KweryDebit
//

KweryDebit::KweryDebit(int amount) : Kwery() {
	act_ = Debit;
	payload_["amount"] = amount;
}

void KweryDebit::handleReply(const QVariant json) {

}
