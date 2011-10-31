#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include <QList>
#include "article.h"
#include "panier.h"
#include <QDoubleSpinBox>
#include "kmodelproduct.h"
#include "kmodelcart.h"
#include <QAbstractItemModel>

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckOutWidget(QWidget *parent = 0);


public slots:
    void addArticle(int id);
    void addArticlePrix();

private:
    QList<KModelCart*> panierlist;
    QDoubleSpinBox *prix;
    QAbstractItemModel *p;
};

#endif // CHECKOUTWIDGET_H
