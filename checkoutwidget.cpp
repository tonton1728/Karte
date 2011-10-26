#include "checkoutwidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>


CheckOutWidget::CheckOutWidget(QWidget *parent) :
    QWidget(parent)
{
    //Ajout d'un layout pour organiser le widget
    this->setLayout(new QGridLayout(this));

    QHBoxLayout *first = new QHBoxLayout(this);
    this->layout()->addItem(first);

    QVBoxLayout *second = new QVBoxLayout(this);
    first->addItem(second);

    //Création d'un bouton pour un article
    QPushButton *but = new QPushButton(this);
    but->setText("Article 1");

    second->addWidget(but);

    //Création d'un champ pour les prix non-prédéfinis
    QDoubleSpinBox *prix = new QDoubleSpinBox(this);
    prix->setSuffix(QString::fromUtf8("€"));
    second->addWidget(prix);


    //Création d'un label (???) pour afficher le panier
    QLabel *panier = new QLabel(this);
    panier->setText("Panier : \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \nBlabla \n ");

    first->addWidget(panier);

    QPushButton *payer = new QPushButton(this);
    payer->setText("Payer");
    this->layout()->addWidget(payer);
}
