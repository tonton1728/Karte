#ifndef RECHARGERWIDGET_H
#define RECHARGERWIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "user.h"

class RechargerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RechargerWidget(QWidget *parent = 0, User* caissier = new User() );

signals:

public slots:
    void Recharger();

private:
    QDoubleSpinBox *rechargermontant;
};

#endif // RECHARGERWIDGET_H
