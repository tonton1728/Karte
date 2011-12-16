#ifndef KREMOTEMODEL_H
#define KREMOTEMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QString>

#include "kommunikator.h"

/**
  Cette classe est la base pour tous les modèles distants. Elle s'occupe
  de la communication réseau avec le serveur pour récupérer les données
  du modèle les stocker dans un tableau interne. Pour implémenter un
  nouveau modèle distant, il suffit de sous-classer cette classe, et
  éventuellement de changer les méthodes pour avoir un comportement plus
  personalisé.

  Attention : il est important de bien définir modelName_ dans le
  constructeur pour que la classe fonctionne correctement.
  */
class KRemoteModel : public QAbstractListModel
{
    Q_OBJECT
public:
	explicit KRemoteModel(Kommunikator *k, QObject *parent = 0);

	enum ModelState {
		Unconnected, Getting, Headers, Fetching, Complete
	};

	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	/*bool canFetchMore(const QModelIndex &parent) const;
	void fetchMore(const QModelIndex &parent);*/

protected:
	// Contient le nom du modèle sur le serveur.
	QString modelName_;
	// Stocke l'index de l'instance.
	int mid_;

private slots:
	void handleKonnState(const Kommunikator::KonnState st);
	void setState(ModelState st);
	void gotModelId(int mid);
	void gotData(QVariantList data);
	void gotHeaders(QVariantList headers);

protected:
	QVariantList data_, hdrs_;
	Kommunikator *k_;
	ModelState st_;

signals:
	void stateChanged(KRemoteModel::ModelState st);

public slots:

};

#endif // KREMOTEMODEL_H
