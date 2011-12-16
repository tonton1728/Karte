#ifndef PAIEMENTWIDGET_H
#define PAIEMENTWIDGET_H

#include <QWidget>
#include "kmodelcart.h"
#include <QAbstractItemModel>
#include "user.h"
#include "protocol/kommunikator.h"

class PaiementWidget : public QWidget
{
    Q_OBJECT
public:
	explicit PaiementWidget(Kommunikator *kom, QWidget *parent = 0, KModelCart* cart = 0, User *caissier = new User());

private:
    QAbstractItemModel *cart_;
    User *caissier_;
	Kommunikator *kom_;

private slots:
	void sendClicked();

signals:
	void sendOperation(int amount);

public slots:

};

#endif // PAIEMENTWIDGET_H
