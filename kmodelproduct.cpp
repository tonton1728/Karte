#include "kmodelproduct.h"

#include <QDebug>

KModelProduct::KModelProduct(Kommunikator* kom, QObject *parent) :
	KRemoteModel(kom, parent)
{
	modelName_ = "Products";
	connect(this, SIGNAL(stateChanged(KRemoteModel::ModelState)), this, SLOT(watchState(KRemoteModel::ModelState)));
}

Product::Product(QObject *parent, QString name, int price, QImage picture, QString script, int id ) :
    QObject(parent), name_(name), price_(price), picture_(picture), script_(script), id_(id)
{
}

void Product::click() {
    emit clicked(this);
}

void KModelProduct::watchState(KRemoteModel::ModelState st) {
	if(st == Complete) {
		foreach(QVariant v, data_) {
			QVariantList r = v.toList();
			products_.append(new Product(this, r[1].toString(), r[2].toInt(), QImage(), r[3].toString(), r[0].toInt()));
		}
	}
}

QList<Product*> *KModelProduct::products() {
	return &products_;
}

Product *KModelProduct::productForIndex(QModelIndex idx) {
	if(idx.row() >= data_.count()) {
		return 0;
	}

	QVariantList r = data_[idx.row()].toList();
	return new Product(this, r[1].toString(), r[2].toInt(), QImage(), r[3].toString(), r[0].toInt());
}
