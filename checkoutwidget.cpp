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


CheckOutWidget::CheckOutWidget(QWidget *parent, User* caissier) :
    QWidget(parent)
{
    if(caissier != 0) {
        KModelProduct *products = new KModelProduct(this->parent());


	//Ajout d'un layout pour organiser le widget
	this->setLayout(new QGridLayout(this));

	QHBoxLayout *first = new QHBoxLayout(this);
	this->layout()->addItem(first);

	QVBoxLayout *second = new QVBoxLayout(this);
	first->addItem(second);

	FlowLayout *flow = new FlowLayout;
	second->addItem(flow);

	// on crée une liste destinée à contenir tous les boutons
	QList<QPushButton*> tbut = QList<QPushButton*>();

	// code des boutons factorisés
	for (int i=0; i< products->rowCount(QModelIndex());i++) {
	    // on ajoute chaque bouton à la liste
	    tbut.append(new QPushButton(this));
	    // on récupère le produit correspondant
	    Product *test = (Product*) products->children().at(i);
	    tbut[i]->setText(test->name());
	    // on ajoute chaque bouton au layout
	    flow->addWidget(tbut[i]);
	    // On utilise deux connects pour pouvoir passer une variable en paramètre
	    connect(tbut[i], SIGNAL(clicked()),test,SLOT(click()));
	    connect(test,SIGNAL(clicked(Product*)),this,SLOT(addArticle(Product*)));
	}


	//Création d'un champ pour les prix non-prédéfinis
	prix = new QDoubleSpinBox(this);
	prix->setSuffix(QString::fromUtf8("€"));
	//Mettre le minimum à -9999 permet de gérer les nombres négatifs
	prix->setMinimum(-9999);
	second->addWidget(prix);

	QPushButton *validateprix = new QPushButton(this);
	validateprix->setText("valider");
	second->addWidget(validateprix);
	connect(validateprix,SIGNAL(clicked()),this,SLOT(addArticlePrix()));

	// modèle qui contient les informations sur le panier
        this->p = new KModelCart(this->parent());


	// on crée le tableau qui va contenir le panier
	this->table = new QTableView(this);
	this->table->setShowGrid(false);
	// On définit que l'on peut sélectionner que des lignes
	this->table->setSelectionBehavior(QAbstractItemView::SelectRows);
	// On associe le model et le tableau
        this->table->setModel(this->p);



	// on ajoute le tableau au layout
	first->addWidget(this->table);

	QPushButton *supprimer = new QPushButton(this);
	supprimer->setText("Supprimer");
	first->addWidget(supprimer);
	connect(supprimer,SIGNAL(clicked()),this, SLOT(delArticle()));

	QPushButton *payer = new QPushButton(this);
	payer->setText("Payer");
	this->layout()->addWidget(payer);
	connect(payer,SIGNAL(clicked()),this, SLOT(payer()));


	this->total = new QLabel(this);
	this->total->setText(QString::number(((KModelCart*)this->p)->Sum()));


	this->layout()->addWidget(this->total);
    }
    else {
	QLabel *label = new QLabel(this);
	label->setText("Veuillez vous logguer");
	this->layout()->addWidget(label);
    }
}


void CheckOutWidget::addArticle(Product* pro) {
    ((KModelCart*)this->p)->addProduct(pro);
    this->total->setText(QString::number(((KModelCart*)this->p)->Sum()));
}

void CheckOutWidget::addArticlePrix() {
    // on multiplie par 100 pour correspondre au model de données qui gère les prix en tant que int
    float price = prix->value()*100;

    ((KModelCart*)this->p)->addProduct(new Product(this->parent(),"ajout manuel", price, QImage(), "",-1 ));


    qDebug() << price;
    this->total->setText(QString::number(((KModelCart*)this->p)->Sum()));


}

void CheckOutWidget::delArticle() {
    // On est obligé d'utiliser une variable intermédiaire parce que la valeur du count change à chaque suppression
    int hack = this->table->selectionModel()->selectedRows().count();

    // On boucle sur l'ensemble des Articles à supprimer
    for(int i=0; i < hack;i++){
	((KModelCart*)this->p)->delProduct(this->table->selectionModel()->selectedRows().at(0).row());
    }

    this->total->setText(QString::number(((KModelCart*)this->p)->Sum()));

}


void CheckOutWidget::payer() {
    emit sendPayer((KModelCart*)this->p);
}
