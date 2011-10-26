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
    qDebug() << "coucou";
    checkState();
}

void MainWindow::checkState() {
    QWidget *todelete = this->centralWidget();

    switch (AS) {
    case Authenticating:
	this->setCentralWidget(lw);
	break;
    case CheckoutMode:
	this->setCentralWidget(cw);
	break;
    default:
	break;
    }
    connect(lw,SIGNAL(loginSuccessful()),this,SLOT(loginSuccess()));
}
