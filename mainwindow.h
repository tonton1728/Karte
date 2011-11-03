#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginwidget.h"
#include "checkoutwidget.h"
#include "rechargerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void loginSuccess();
    void Recharger();

private:
    enum AppState {
	Authenticating, CheckoutMode, RechargerMode    };
    AppState AS;
    LoginWidget *lw;
    CheckOutWidget *cw;
    RechargerWidget *rw;
    void checkState();
};

#endif // MAINWINDOW_H
