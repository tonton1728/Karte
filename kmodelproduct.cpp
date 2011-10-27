#include "kmodelproduct.h"

KModelProduct::KModelProduct(QObject *parent) :
	QAbstractListModel(parent)
{
	products_ << new Product("prout", 4200, QImage(), "", this);
	products_ << new Product("caca", 4300, QImage(), "", this);
	products_ << new Product("pipi", 4567, QImage(), "", this);
	products_ << new Product("vomit", 1234, QImage(), "", this);
}

Product::Product(QString name, int price, QImage picture, QString script, QObject *parent) :
	name_(name), price_(price), picture_(picture), script_(script), QObject(parent)
{

}

int KModelProduct::rowCount(const QModelIndex &parent) const {
	return products_.count();
}

QVariant KModelProduct::data(const QModelIndex &index, int role) const {
	if(!index.isValid() || index.row() >= products_.count())
		return QVariant();

	switch(role) {
	case Qt::DisplayRole:
		return products_.at(index.row())->name();
	default:
		return QVariant();
	}
}

QVariant KModelProduct::headerData(int section, Qt::Orientation orientation, int role) const {
	if(role != Qt::DisplayRole)
		return QVariant();

	return QString("Product");
}
