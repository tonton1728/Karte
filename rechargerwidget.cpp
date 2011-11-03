#include "rechargerwidget.h"
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

RechargerWidget::RechargerWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    this->setLayout(l);

    QVBoxLayout *llabel = new QVBoxLayout(this);
    this->layout()->addItem(llabel);
    QLabel *label = new QLabel(this);
    label->setText(QString::fromUtf8("Indiquez le montant à recharger sur la carte"));
    llabel->addWidget(label);

    QDoubleSpinBox *rechargermontant = new QDoubleSpinBox(this);
    rechargermontant->setSuffix(QString::fromUtf8("€"));
    this->layout()->addWidget(rechargermontant);

    QPushButton *valider = new QPushButton(this);
    valider->setText("Valider");
    this->layout()->addWidget(valider);
}
