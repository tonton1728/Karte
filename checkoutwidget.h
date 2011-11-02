#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include <QList>
#include "article.h"
#include <QDoubleSpinBox>
#include "kmodelproduct.h"
#include "kmodelcart.h"
#include <QAbstractItemModel>
#include <QTableView>

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckOutWidget(QWidget *parent = 0);


public slots:
    void addArticle(Product* pro);
    void addArticlePrix();
    void delArticle();

private:
    QList<KModelCart*> panierlist;
    QDoubleSpinBox *prix;
    QAbstractItemModel *p;
    QTableView *table;
};

#endif // CHECKOUTWIDGET_H
