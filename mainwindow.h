#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loginwidget.h"
#include "checkoutwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void loginSuccess();

private:
    enum AppState {
	Authenticating, CheckoutMode    };
    AppState AS;
    LoginWidget *lw;
    CheckOutWidget *cw;
    void checkState();
};

#endif // MAINWINDOW_H
