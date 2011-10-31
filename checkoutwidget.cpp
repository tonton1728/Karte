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
#include <QTableView>
#include "article.h"
#include <QImage>


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
    second->addItem(flow);


    //Création d'un bouton pour un article
    //@TODO factoriser ce code
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
    prix = new QDoubleSpinBox(this);
    prix->setSuffix(QString::fromUtf8("€"));
    second->addWidget(prix);

    QPushButton *validateprix = new QPushButton(this);
    validateprix->setText("valider");
    second->addWidget(validateprix);
    connect(validateprix,SIGNAL(clicked()),this,SLOT(addArticlePrix()));


    //Création d'un label (???) pour afficher le panier
    QLabel *lpanier = new QLabel(this);
    lpanier->setText("Panier : \nBlabla \nBlabla \nBlabla \n ");

    first->addWidget(lpanier);

    QPushButton *payer = new QPushButton(this);
    payer->setText("Payer");
    this->layout()->addWidget(payer);



//    QListView *table = new QListView(this);
//    table->setModel(this->panierlist->first());
//    this->layout()->addWidget(table);
}


void CheckOutWidget::addArticle(int id) {
    qDebug() << id << endl;
}

void CheckOutWidget::addArticlePrix() {
    float price = prix->value();
    KModelCart *p = new KModelCart(this);

    QTableView *table = new QTableView(this);
    table->setShowGrid(false);

    table->setModel(p);
    this->layout()->addWidget(table);

    panierlist.push_back(p);

    qDebug() << price;
}
