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
#include <QModelIndex>

CheckOutWidget::CheckOutWidget(QWidget *parent) :
    QWidget(parent)
{
    KModelProduct *products = new KModelProduct(this);


    //Ajout d'un layout pour organiser le widget
    this->setLayout(new QGridLayout(this));

    QHBoxLayout *first = new QHBoxLayout(this);
    this->layout()->addItem(first);

    QVBoxLayout *second = new QVBoxLayout(this);
    first->addItem(second);

    FlowLayout *flow = new FlowLayout;
    second->addItem(flow);

    QList<QPushButton*> tbut = QList<QPushButton*>();

    // code des boutons factorisés
    for (int i=0; i< products->rowCount(QModelIndex());i++) {
	tbut.append(new QPushButton(this));
//	 tbut[i]->setText("test");
	 tbut[i]->setText(products->index(i,0,QModelIndex()).data().toString());
	 flow->addWidget(tbut[i]);
    }

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

    this->p = new KModelCart(this);

    QTableView *table = new QTableView(this);
    table->setShowGrid(false);
    table->setModel(this->p);
    first->addWidget(table);

    QPushButton *payer = new QPushButton(this);
    payer->setText("Payer");
    this->layout()->addWidget(payer);




}


void CheckOutWidget::addArticle(int id) {
    qDebug() << id << endl;
}

void CheckOutWidget::addArticlePrix() {
    // on multiplie par 100 pour correspondre au model de données qui gère les prix en tant que int
    float price = prix->value()*100;

    ((KModelCart*)this->p)->addProduct(new Product("ajout manuel", price, QImage(), "", this));




    qDebug() << price;
}
