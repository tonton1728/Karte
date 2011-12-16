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
#include <QPushButton>
#include "user.h"
#include "flowlayout.h"

#include "protocol/kommunikator.h"

class CheckOutWidget : public QWidget
{
    Q_OBJECT
public:
	explicit CheckOutWidget(Kommunikator *kom, QWidget *parent = 0, User* caissier = 0);


public slots:
    void addArticle(Product* pro);
    void addArticlePrix();
    void delArticle();
    void payer();

private slots:
	void modelStateChanged(KRemoteModel::ModelState st);

private:
    QList<KModelCart*> panierlist;
    QDoubleSpinBox *prix;
    QAbstractItemModel *p;
    QTableView *table;
    QLabel *total;
	Kommunikator *kom_;
	KModelProduct *products;
	QList<QPushButton*> tbut;
	User* operator_;
	FlowLayout *flow;

signals:
    void sendPayer(KModelCart*);
};

#endif // CHECKOUTWIDGET_H
