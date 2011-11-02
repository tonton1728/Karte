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
	Product *test = (Product*) products->children().at(i);
	tbut[i]->setText(test->name());
	flow->addWidget(tbut[i]);
	connect(tbut[i], SIGNAL(clicked()),test,SLOT(click()));
	connect(test,SIGNAL(clicked(Product*)),this,SLOT(addArticle(Product*)));
    }


    //Création d'un champ pour les prix non-prédéfinis
    prix = new QDoubleSpinBox(this);
    prix->setSuffix(QString::fromUtf8("€"));
    prix->setMinimum(-9999);
    second->addWidget(prix);

    QPushButton *validateprix = new QPushButton(this);
    validateprix->setText("valider");
    second->addWidget(validateprix);
    connect(validateprix,SIGNAL(clicked()),this,SLOT(addArticlePrix()));


    // tableau pour l'affichage du panier
    this->p = new KModelCart(this);

    this->table = new QTableView(this);
    this->table->setShowGrid(false);
    this->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->table->setModel(this->p);

    first->addWidget(this->table);

    QPushButton *supprimer = new QPushButton(this);
    supprimer->setText("Supprimer");
    first->addWidget(supprimer);
    connect(supprimer,SIGNAL(clicked()),this, SLOT(delArticle()));

    QPushButton *payer = new QPushButton(this);
    payer->setText("Payer");
    this->layout()->addWidget(payer);




}


void CheckOutWidget::addArticle(Product* pro) {
    ((KModelCart*)this->p)->addProduct(pro);
}

void CheckOutWidget::addArticlePrix() {
    // on multiplie par 100 pour correspondre au model de données qui gère les prix en tant que int
    float price = prix->value()*100;

    ((KModelCart*)this->p)->addProduct(new Product("ajout manuel", price, QImage(), "",-1, this));




    qDebug() << price;
}

void CheckOutWidget::delArticle() {
    int hack = this->table->selectionModel()->selectedRows().count();

    for(int i=0; i < hack;i++){
	((KModelCart*)this->p)->delProduct(this->table->selectionModel()->selectedRows().at(0).row());
    }



}
