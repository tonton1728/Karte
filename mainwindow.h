#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginwidget.h"
#include "checkoutwidget.h"
#include "rechargerwidget.h"
#include "user.h"
#include "kmodelcart.h"
#include "paiementwidget.h"
#include <QMenu>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void loginSuccess(User *caissier);
    void Recharger();
    void Payer(KModelCart*);

private:
    enum AppState {
	Authenticating, CheckoutMode, RechargerMode, PaiementMode    };
    LoginWidget *lw;
    CheckOutWidget *cw;
    RechargerWidget *rw;
    PaiementWidget *pw;
    AppState AS;

    void checkState();
    User *caissier;
    QMenu *menu;
    KModelCart *cart;
};

#endif // MAINWINDOW_H
