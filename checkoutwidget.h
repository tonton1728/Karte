#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckOutWidget(QWidget *parent = 0);


public slots:
    void addArticle(int id);
};

#endif // CHECKOUTWIDGET_H
