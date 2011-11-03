#include "mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    lw(new LoginWidget(this)),
    cw(0),
    rw(0),
    AS(Authenticating)
{
    checkState();
    connect(lw,SIGNAL(loginSuccessful()),this,SLOT(loginSuccess()));
    QMenu *menu = new QMenu("File");
    this->menuBar()->addMenu(menu);
    menu->addAction("Recharger",this,SLOT(Recharger()));

}

void MainWindow::loginSuccess() {
    AS = CheckoutMode;
    checkState();
}

void MainWindow::checkState() {

    switch (AS) {
    case Authenticating:
	this->setCentralWidget(lw);
	break;
    case CheckoutMode:
	cw = new CheckOutWidget(this);
	this->setCentralWidget(cw);
	break;
    case RechargerMode:
	rw = new RechargerWidget(this);
	this->setCentralWidget(rw);
	break;
    default:
	break;
    }
}

void MainWindow::Recharger() {
    AS = RechargerMode;
    checkState();
}
