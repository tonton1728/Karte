#include "checkoutwidget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "flowlayout.h"
#include <QSpacerItem>
#include "article.h"

CheckOutWidget::CheckOutWidget(QWidget *parent) :
    QWidget(parent)
{
    //Ajout d'un layout pour organiser le widget
    this->setLayout(new QGridLayout(this));

    QHBoxLayout *first = new QHBoxLayout(this);
    this->layout()->addItem(first);

    QVBoxLayout *second = new QVBoxLayout(this);
    first->addItem(second);



    FlowLayout *flow = new FlowLayout;
    //QVBoxLayout *flow = new QVBoxLayout(this);
    second->addItem(flow);


    //Création d'un bouton pour un article
    //@ factoriser ce code
    QPushButton *but = new QPushButton(this);
    but->setText("Article 1");
    flow->addWidget(but);
    Article *a0 = new Article(this,0);

    connect(but,SIGNAL(clicked()),a0,SLOT(click()));
    connect(a0,SIGNAL(sendId(int)),this, SLOT(addArticle(int)));


//    QPushButton *but1 = new QPushButton(this);
//    but1->setText("Article 1");
//    flow->addWidget(but1);

//    QPushButton *but2 = new QPushButton(this);
//    but2->setText("Article 1");
//    flow->addWidget(but2);

//    QPushButton *but3 = new QPushButton(this);
//    but3->setText("Article 1");
//    flow->addWidget(but3);

//    QPushButton *but4 = new QPushButton(this);
//    but4->setText("Article 1");
//    flow->addWidget(but4);

//    QPushButton *but5 = new QPushButton(this);
//    but5->setText("Article 1");
//    flow->addWidget(but5);


    //Création d'un champ pour les prix non-prédéfinis
    QDoubleSpinBox *prix = new QDoubleSpinBox(this);
    prix->setSuffix(QString::fromUtf8("€"));
    second->addWidget(prix);


    //Création d'un label (???) pour afficher le panier
    QLabel *panier = new QLabel(this);
    panier->setText("Panier : \nBlabla \nBlabla \nBlabla \n ");

    first->addWidget(panier);

    QPushButton *payer = new QPushButton(this);
    payer->setText("Payer");
    this->layout()->addWidget(payer);
}


void CheckOutWidget::addArticle(int id) {
    qDebug() << id << endl;
}
