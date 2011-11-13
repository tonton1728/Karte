#ifndef KMODELCART_H
#define KMODELCART_H

#include <QAbstractTableModel>
#include <QList>
#include "kmodelproduct.h"
#include <QVariant>

class KModelCart : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit KModelCart(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void addProduct(Product *p);
    void delProduct(int row);
    float Sum();
    void setProducts(QList<Product*> ps);


    QList<Product*> products() {return products_;}

signals:

public slots:


private:
    QList<Product*> products_;
};

#endif // KMODELCART_H
