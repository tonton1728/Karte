#include "kmodelcart.h"
#include <QDebug>

KModelCart::KModelCart(QObject *parent) :
    QAbstractTableModel(parent)
{

}


int KModelCart::rowCount(const QModelIndex &) const {
    return products_.count();
}

int KModelCart::columnCount(const QModelIndex &) const {
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
    case Qt::UserRole:
	return index.row();
    default:
	return QVariant();
    }
}

QVariant KModelCart::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole)
	return QVariant();
    if (orientation == Qt::Vertical)
	return QString("Produit");
    else if (orientation == Qt::Horizontal && section == 0)
	return QString("nom");
    else if (orientation == Qt::Horizontal && section == 1)
	return QString("prix");
    return QString("vertical");
}

void KModelCart::addProduct(Product *p) {
    beginInsertRows(QModelIndex(),products_.count(),products_.count());
    products_ << p;
    endInsertRows();
}

void KModelCart::delProduct(int row) {
    beginRemoveRows(QModelIndex(),row,row);
    products_.removeAt(row);
    endRemoveRows();
}

float KModelCart::Sum() {
    int Sum = 0;
    foreach(Product *f, products_) {
	Sum += f->price();
    }
   return Sum/100.0;
}

void KModelCart::setProducts(QList<Product *> ps) {
    this->products_ = ps;
}
