#ifndef KMODELPRODUCT_H
#define KMODELPRODUCT_H

#include <QAbstractListModel>
#include <QImage>
#include <QString>
#include <QList>

#include "protocol/kremotemodel.h"

class Product : public QObject {
	Q_OBJECT

public:
    explicit Product( QObject *parent = 0, QString name = "", int price = 0, QImage picture = QImage(), QString script = "", int id=0);

public:
	inline QString name() { return name_; }
	inline int price() { return price_; }
	inline QImage picture() { return picture_; }
	inline QString script() { return script_; }
	inline int id() { return id_; }

public slots:
	void click();

signals:
	void clicked(Product* pro);

private:
	QString name_;
	int price_;
	QImage picture_;
	QString script_;
	int id_;
};

class KModelProduct : public KRemoteModel
{
    Q_OBJECT
public:
	explicit KModelProduct(Kommunikator *kom, QObject *parent = 0);

	QList<Product*> *products();
	Product *productForIndex(QModelIndex idx);

private slots:
	void watchState(KRemoteModel::ModelState st);

private:
	QList<Product*> products_;
};

#endif // KMODELPRODUCT_H
