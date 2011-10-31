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
	    return QString::number(products_.at(index.row())->price()/100,'g',2) + QString::fromUtf8("€");
	    //return QString("%.2lf").arg(products_.at(index.row())->price()/100.0);
	    //return QString("test");
	}
	else
	    return QVariant();
	break;
    default:
	qDebug() << "here I am" << role;
	return QString("hey");
    }
}

QVariant KModelCart::headerData(int section, Qt::Orientation orientation, int role) const {

}
