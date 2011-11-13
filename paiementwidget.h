#ifndef PAIEMENTWIDGET_H
#define PAIEMENTWIDGET_H

#include <QWidget>
#include "kmodelcart.h"
#include <QAbstractItemModel>
#include "user.h"

class PaiementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaiementWidget(QWidget *parent = 0, KModelCart* cart = 0, User *caissier = new User());


private:
    QAbstractItemModel *cart_;
    User *caissier_;
signals:

public slots:

};

#endif // PAIEMENTWIDGET_H
