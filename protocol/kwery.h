#ifndef KWERY_H
#define KWERY_H

#include <QObject>
#include <QVariant>

#include "kommunikator.h"

class Kwery : public QObject
{
    Q_OBJECT

public:
    explicit Kwery(QObject *parent = 0);
	friend class Kommunikator;

	enum KweryAction {
			Init, Debit, Credit, AuthCheckout, ModelGet, ModelData,
			ModelCheckMoreData, ModelGetMoreData,
			ModelFilter, ModelHeaders
	};
	virtual QString actionToString();

signals:
	void error(int code, QString name);

protected slots:
	void handleReply(int seq, const QVariant json);
	void handleError(int seq, const int code, const QString name);

protected:
	virtual void handleReply(const QVariant json) = 0;
	virtual void handleError(const int code, const QString name);
	QVariant makeMessage();

	int seq_;
	KweryAction act_;
	QVariantMap payload_;
};

//-------------------------------------------------------------------

class KweryInit : public Kwery {
	Q_OBJECT

public:
	KweryInit();

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void done();
};

//-------------------------------------------------------------------

class KweryAuthCheckout : public Kwery {
	Q_OBJECT

public:
	KweryAuthCheckout(int id);

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void authSuccess();
	void authFail();
};

//-------------------------------------------------------------------

class KweryModelGet : public Kwery {
	Q_OBJECT

public:
	KweryModelGet(QString name);
	virtual QString actionToString();

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void gotModel(int mid);

private:
	QString name;
};

//-------------------------------------------------------------------

class KweryModelData : public Kwery {
	Q_OBJECT

public:
	KweryModelData(int mid);

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void gotData(QVariantList data);
};

//-------------------------------------------------------------------

class KweryModelHeaders : public Kwery {
	Q_OBJECT

public:
	KweryModelHeaders(int mid);

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void gotHeaders(QVariantList headers);
};

//-------------------------------------------------------------------

class KweryModelCheckMoreData : public Kwery {
	Q_OBJECT

public:
	KweryModelCheckMoreData(int mid);

protected slots:
	virtual void handleReply(const QVariant json);

signals:
	void moreDataAvailable(bool more);
};

//-------------------------------------------------------------------

class KweryDebit : public Kwery {
	Q_OBJECT

public:
	KweryDebit(int amount);

protected slots:
	virtual void handleReply(const QVariant json);
};

#endif // KWERY_H
