#include "rechargerwidget.h"
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QTableView>

RechargerWidget::RechargerWidget(QWidget *parent, User* caissier) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout(this));

    if (caissier!=0) {
	QVBoxLayout *llabel = new QVBoxLayout(this);
	this->layout()->addItem(llabel);


	QLabel *label = new QLabel(this);
	label->setText(QString::fromUtf8("Indiquez le montant à recharger sur la carte"));
	llabel->addWidget(label);

	this->rechargermontant = new QDoubleSpinBox(this);
	this->rechargermontant->setSuffix(QString::fromUtf8("€"));
	this->layout()->addWidget(this->rechargermontant);

	QPushButton *valider = new QPushButton(this);
	valider->setText("Valider");
	this->layout()->addWidget(valider);

	connect(valider,SIGNAL(clicked()),this,SLOT(Recharger()));

    }
    else {
	QLabel *label = new QLabel(this);
	label->setText("Veuillez vous logguer");
	this->layout()->addWidget(label);
    }
}

void RechargerWidget::Recharger() {
    qDebug() << this->rechargermontant->value() ;
}
