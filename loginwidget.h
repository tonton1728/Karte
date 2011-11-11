#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "user.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);

private:
    QLabel *text;
    QLineEdit *login;
    QPushButton *button;


signals:
    void loginSuccessful(User*);

private slots:
    void checkThat();

};

#endif // LOGINWIDGET_H
