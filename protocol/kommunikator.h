#ifndef KOMMUNIKATOR_H
#define KOMMUNIKATOR_H

#include <QObject>

#include "kprotocoljsonreceiver.h"
#include "kwery.h"

// Needed in order to be friend
class Kwery;

/**
  Classe de base du protocole, elle s'assure de la communication avec le
  serveur. Elle s'appuie sur KProtocolJsonReceiver pour fonctionner.
  */
class Kommunikator : public QObject
{
    Q_OBJECT
public:
    explicit Kommunikator(QObject *parent = 0);

	/**
	  Établit la communication avec le serveur, envoie les messages
	  d'initialisation.
	  */
	bool konnect(QString host, quint16 port = 0x666, bool secure = true);
	/**
	  Envoie une requête vers le serveur
	  */
	void sendKwery(Kwery *kw);
	/**
	  Authentifie une caisse
	  Cette fonction est un proof of concept
	  */
	void authCheckout(int id);

	/**
	  Défini les états de connexion possibles
	  */
	enum KonnState {
		Unestablished, Established, Authenticated
	};

	/**
	  Retourne l'état de connexion actuel
	  */
	inline KonnState state() const { return ks_; }

signals:
	/**
	  Signale de l'arrivée d'une reponse
	  */
	void gotReply(int seq, QVariant json);
	/**
	  Signale de l'arrivee d'une erreur
	  */
	void gotError(int seq, int code, QString name);
	/**
	  Un message dans un format invalide a été reçu
	  */
	void invalidMessage(QVariant json);
	/**
	  L'état de connexion a changé
	  */
	void stateChanged(Kommunikator::KonnState state);

public slots:
	/**
	  Ce slot est appellé quand des données arrivent
	  */
	void handleIncoming(QVariant json);

private slots:
	/**
	  Défini un nouvel état et agit en conséquence
	  */
	void setState(KonnState state);
	/**
	  La séquence d'initialisation est terminée
	  */
	void initDone();
	/**
	  L'initialisation a échoué, probablement à cause de la non
	  correspondance des numéros de version des protocoles.
	  */
	void initFailed(int,QString);
	/**
	  L'authentification a réussi
	  */
	void authSuccess();
	/**
	  L'authentification a échoué
	  */
	void authFailed();

private:
	KProtocolJsonReceiver jsr_;
	int seq_;
	KonnState ks_;
};

#endif // KOMMUNIKATOR_H
