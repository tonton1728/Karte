	#include "mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	lw(new LoginWidget(this)),
	cw(0),
	rw(0),
	pw(0),
	AS(Authenticating),
	caissier(0),
	menu(0)
{
	checkState();
	connect(lw,SIGNAL(loginSuccessful(User*)),this,SLOT(loginSuccess(User*)));
	kom.konnect("loc.telnet-tl1.org", 8000, false);
}

void MainWindow::loginSuccess(User* caissier) {
	kom.authCheckout(42);
	this->caissier = caissier;
	AS = CheckoutMode;
	checkState();
}

void MainWindow::checkState() {
	if (caissier!=0 && menu == 0) {
		menu = new QMenu("File");
		this->menuBar()->addMenu(menu);
		menu->addAction("Recharger",this,SLOT(Recharger()));
		menu->addAction("caisse",this,SLOT(Caisse()));
	}

	switch (AS) {
		case Authenticating:
			this->setCentralWidget(lw);
			break;
		case CheckoutMode:
			cw = new CheckoutWidgetBis(&kom, this);
			this->setCentralWidget(cw);
			connect(cw, SIGNAL(sendPayer(KModelCart*)), this, SLOT(Payer(KModelCart*)));
			break;
		case RechargerMode:
			rw = new RechargerWidget(this, this->caissier);
			this->setCentralWidget(rw);
			break;
		case PaiementMode:
			pw = new PaiementWidget(&kom, this, this->cart, this->caissier);
			this->setCentralWidget(pw);
			break;
		default:
			break;
	}
}

void MainWindow::Recharger() {
	AS = RechargerMode;
	checkState();
}

void MainWindow::Payer(KModelCart *cart) {
	AS = PaiementMode;
	this->cart = cart;
	checkState();
}

void MainWindow::Caisse() {
	AS = CheckoutMode;
	checkState();
}
