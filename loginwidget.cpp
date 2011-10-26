#include "loginwidget.h"
#include <QVBoxLayout>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(new QVBoxLayout(this));

    text = new QLabel(this);
    text->setText("Bonjour, veuillez vous identifier");
    text->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(text);

    login = new QLineEdit(this);
    this->layout()->addWidget(login);
    connect(login, SIGNAL(returnPressed()), this, SLOT(checkThat()));

    button = new QPushButton(this);
    button->setText("Valider");
    this->layout()->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(checkThat()));
}

void LoginWidget::checkThat() {
    if(login->text() == "coucou") {
	qDebug() << "yeaaaaah";
	emit loginSuccessful();
    }
}
