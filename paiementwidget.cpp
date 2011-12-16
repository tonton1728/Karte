#include "paiementwidget.h"
#include <QDebug>
#include <QModelIndex>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>
#include <QPushButton>

#include "protocol/kwery.h"

PaiementWidget::PaiementWidget(Kommunikator *kom, QWidget *parent, KModelCart *cart, User *caissier) :
	QWidget(parent), cart_(cart), caissier_(caissier), kom_(kom)
{
	this->setLayout(new QVBoxLayout() );
	if (this->caissier_ != 0) {
		if (this->cart_->rowCount(QModelIndex()) == 0) {
			QLabel *label = new QLabel(this);
			label->setText("really, cart empty ?");
			this->layout()->addWidget(label);
		} else {
			QTableView *table = new QTableView(this);
			table->setShowGrid(false);
			table->setSelectionBehavior(QAbstractItemView::SelectRows);
			table->setModel(this->cart_);

			this->layout()->addWidget(table);

			QPushButton *send = new QPushButton(this);
			this->layout()->addWidget(send);
			send->setText("Envoyer");
			connect(send, SIGNAL(clicked()), this, SLOT(sendClicked()));
		}
	}
	else {
		QLabel *label = new QLabel(this);
		label->setText("Veuillez vous logguer");
		this->layout()->addWidget(label);
	}
}

void PaiementWidget::sendClicked() {
	int price = ((KModelCart*)cart_)->Sum() * 100;

	Kwery *kw = new KweryDebit(price);
	kom_->sendKwery(kw);

	emit sendOperation(price);
}
