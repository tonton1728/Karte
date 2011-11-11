#include "kmodelproduct.h"

KModelProduct::KModelProduct(QObject *parent) :
	QAbstractListModel(parent)
{
	products_ << new Product(this,"prout", 4200, QImage(), "",1);
	products_ << new Product(this,"caca", 4300, QImage(), "",2);
	products_ << new Product(this,"pipi", 4567, QImage(), "",3);
	products_ << new Product(this,"vomit", 1234, QImage(), "",4 );
}

Product::Product(QObject *parent, QString name, int price, QImage picture, QString script, int id ) :
    QObject(parent), name_(name), price_(price), picture_(picture), script_(script), id_(id)
{

}

void Product::click() {
    emit clicked(this);
}

int KModelProduct::rowCount(const QModelIndex &) const {
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

QVariant KModelProduct::headerData(int , Qt::Orientation , int role) const {
	if(role != Qt::DisplayRole)
		return QVariant();

	return QString("Product");
}
