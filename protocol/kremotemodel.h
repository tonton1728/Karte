#ifndef KREMOTEMODEL_H
#define KREMOTEMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QString>

#include "kommunikator.h"

class KRemoteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KRemoteModel(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	bool canFetchMore(const QModelIndex &parent) const;
	void fetchMore(const QModelIndex &parent);

private:
	static const QString modelName_;
	int mid_;

signals:

public slots:

};

#endif // KREMOTEMODEL_H
