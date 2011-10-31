#include "kmodelcart.h"
#include <QDebug>

KModelCart::KModelCart(QObject *parent) :
    QAbstractTableModel(parent)
{
    products_ << new Product("prout", 4200, QImage(), "", this);
    products_ << new Product("caca", 4300, QImage(), "", this);
    products_ << new Product("pipi", 4567, QImage(), "", this);
    products_ << new Product("vomit", 1234, QImage(), "", this);
}

int KModelCart::rowCount(const QModelIndex &parent) const {
    return products_.count();
}

int KModelCart::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant KModelCart::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= products_.count() || index.column() >= 2)
	return QVariant();
    switch(role) {
    case Qt::DisplayRole:
	if (index.column() == 0) {
	    return products_.at(index.row())->name();
	}
	else if (index.column() == 1) {
	    return QString::number(products_.at(index.row())->price()/100.0,'g',8) + QString::fromUtf8("€");
	}
	else
	    return QVariant();
	break;
    case Qt::TextAlignmentRole:
	if (index.column() == 0)
	    return int(Qt::AlignLeft | Qt::AlignVCenter);
	else if (index.column() == 1)
	    return int(Qt::AlignRight | Qt::AlignVCenter);
    default:
	qDebug() << "here I am" << role;
	return QVariant();
    }
}

QVariant KModelCart::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
	return QVariant();
    return QString("Product");
}

void KModelCart::addProduct(Product *p) {
    beginInsertRows(QModelIndex(),products_.count(),products_.count());
    products_ << p;
    endInsertRows();
}
