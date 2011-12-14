#include "paiementwidget.h"
#include <QDebug>
#include <QModelIndex>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>


PaiementWidget::PaiementWidget(QWidget *parent, KModelCart *cart, User *caissier) :
    QWidget(parent), cart_(cart), caissier_(caissier)
{
    this->setLayout(new QVBoxLayout() );
    if (this->caissier_ != 0) {
	if (this->cart_->rowCount(QModelIndex()) == 0) {
	    QLabel *label = new QLabel(this);
	    label->setText("really, cart empty ?");
	    this->layout()->addWidget(label);
	}
        else {


            qDebug() << this->cart_->data(this->cart_->index(1,0),Qt::DisplayRole);

	    QTableView *table = new QTableView(this);
            table->setShowGrid(false);
            table->setSelectionBehavior(QAbstractItemView::SelectRows);
            table->setModel(this->cart_);

	    this->layout()->addWidget(table);
            qDebug() << this->cart_->data(this->cart_->index(1,1),Qt::DisplayRole) << "wut";

        }
    }
    else {
	QLabel *label = new QLabel(this);
	label->setText("Veuillez vous logguer");
	this->layout()->addWidget(label);
    }
}
