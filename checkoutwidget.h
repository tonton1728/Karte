#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include <QVector>
#include "article.h"
#include "panier.h"
#include <QDoubleSpinBox>

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckOutWidget(QWidget *parent = 0);


public slots:
    void addArticle(int id);
    void addArticlePrix();

private:
    QVector<panier> *panierlist;
    QDoubleSpinBox *prix;
};

#endif // CHECKOUTWIDGET_H
