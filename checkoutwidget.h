#ifndef CHECKOUTWIDGET_H
#define CHECKOUTWIDGET_H

#include <QWidget>
#include <QList>
#include <QDoubleSpinBox>
#include "kmodelproduct.h"
#include "kmodelcart.h"
#include <QAbstractItemModel>
#include <QTableView>
#include <QLabel>

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckOutWidget(QWidget *parent = 0);


public slots:
    void addArticle(Product* pro);
    void addArticlePrix();
    void delArticle();
    void payer();

private:
    QList<KModelCart*> panierlist;
    QDoubleSpinBox *prix;
    QAbstractItemModel *p;
    QTableView *table;
    QLabel *total;
};

#endif // CHECKOUTWIDGET_H
