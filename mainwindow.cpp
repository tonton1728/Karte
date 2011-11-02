#include "mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    lw(new LoginWidget(this)),
    cw(0),
    AS(Authenticating)
{
    checkState();

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
    default:
	break;
    }
    connect(lw,SIGNAL(loginSuccessful()),this,SLOT(loginSuccess()));
}
