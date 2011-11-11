#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginwidget.h"
#include "checkoutwidget.h"
#include "rechargerwidget.h"
#include "user.h"
#include <QMenu>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void loginSuccess(User *caissier);
    void Recharger();

private:
    enum AppState {
	Authenticating, CheckoutMode, RechargerMode    };
    LoginWidget *lw;
    CheckOutWidget *cw;
    RechargerWidget *rw;
    AppState AS;

    void checkState();
    User *caissier;
    QMenu *menu;
};

#endif // MAINWINDOW_H
