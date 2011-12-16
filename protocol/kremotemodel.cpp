#include "kremotemodel.h"
#include "kwery.h"

#include <QDebug>

KRemoteModel::KRemoteModel(Kommunikator *k, QObject *parent) :
	QAbstractListModel(parent),
	k_(k),
	st_(Unconnected)
{
	modelName_ = "Void";

	connect(k_, SIGNAL(stateChanged(Kommunikator::KonnState)), this, SLOT(handleKonnState(Kommunikator::KonnState)));
	handleKonnState(k_->state());
}

void KRemoteModel::setState(ModelState st) {
	Kwery *kw;

	st_ = st;

	switch(st_) {
	case Getting:
		kw = new KweryModelGet(modelName_);
		connect(((KweryModelGet*)kw), SIGNAL(gotModel(int)), this, SLOT(gotModelId(int)));
		k_->sendKwery(kw);
		break;
	case Headers:
		kw = new KweryModelHeaders(mid_);
		connect(((KweryModelHeaders*)kw), SIGNAL(gotHeaders(QVariantList)), this, SLOT(gotHeaders(QVariantList)));
		k_->sendKwery(kw);
		break;
	case Fetching:
		kw = new KweryModelData(mid_);
		connect(((KweryModelData*)kw), SIGNAL(gotData(QVariantList)), this, SLOT(gotData(QVariantList)));
		k_->sendKwery(kw);
		break;
	case Complete:
		qDebug() << "Model" << modelName_ << "complete";
		qDebug() << hdrs_;
		qDebug() << data_;
	default:
		break;
	}

	emit stateChanged(st);
}

void KRemoteModel::handleKonnState(const Kommunikator::KonnState st) {
	switch(st) {
	case Kommunikator::Unestablished:
	case Kommunikator::Established:
		setState(Unconnected);
		break;
	case Kommunikator::Authenticated:
		if(st_ == Unconnected) {
			setState(Getting);
		}
		break;
	}
}

void KRemoteModel::gotModelId(int mid) {
	if(st_ == Getting) {
		mid_ = mid;
		setState(Headers);
	}
}

void KRemoteModel::gotHeaders(QVariantList headers) {
	if(st_ == Headers) {
		emit beginInsertColumns(QModelIndex(), 0, headers.length() - 1);
		hdrs_ = headers;
		emit endInsertColumns();
		setState(Fetching);
	}
}

void KRemoteModel::gotData(QVariantList data) {
	if(st_ == Fetching) {
		emit beginInsertRows(QModelIndex(), 0, data.length() - 1);
		this->data_ = data;
		emit endInsertRows();

		setState(Complete);
	}
}

int KRemoteModel::rowCount(const QModelIndex &parent) const {
	if(st_ != Complete) {
		return 0;
	} else {
		return data_.size();
	}
}

int KRemoteModel::columnCount(const QModelIndex &parent) const {
	if(st_ != Complete) {
		return 0;
	} else {
		return hdrs_.size();
	}
}

QVariant KRemoteModel::data(const QModelIndex &index, int role) const {
	if(st_ != Complete) {
		return QVariant();
	}

	if(!index.isValid()) {
		return QVariant();
	}

	if(index.row() >= data_.size() || index.column() >= hdrs_.size()) {
		return QVariant();
	}

	if(role == Qt::DisplayRole) {
		return data_[index.row()].toList()[index.column() + 1];
	} else {
		return QVariant();
	}
}

QVariant KRemoteModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(role != Qt::DisplayRole) {
		return QVariant();
	}

	if(orientation == Qt::Horizontal && section < hdrs_.size()) {
		return hdrs_[section];
	} else if(orientation == Qt::Vertical && section < data_.size()) {
		return data_[section].toList()[0];
	}

	return QVariant();
}
