#include "kmodelproduct.h"

KModelProduct::KModelProduct(QObject *parent) :
	QAbstractListModel(parent)
{
	products_ << new Product("prout", 4200, QImage(), "",1, this);
	products_ << new Product("caca", 4300, QImage(), "",2, this);
	products_ << new Product("pipi", 4567, QImage(), "",3, this);
	products_ << new Product("vomit", 1234, QImage(), "",4, this);
}

Product::Product(QString name, int price, QImage picture, QString script, int id, QObject *parent) :
    name_(name), price_(price), picture_(picture), script_(script), id_(id), QObject(parent)
{

}

void Product::click() {
    emit clicked(this);
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
