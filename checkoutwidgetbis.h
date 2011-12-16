#ifndef CHECKOUTWIDGETBIS_H
#define CHECKOUTWIDGETBIS_H

#include <QWidget>
#include "kmodelcart.h"
#include "kmodelproduct.h"
#include "protocol/kommunikator.h"

namespace Ui {
    class CheckoutWidgetBis;
}

/**
  Réimplémentation de CheckoutWidget pour mieux adhérer au principe modele/vue.
  */
class CheckoutWidgetBis : public QWidget
{
    Q_OBJECT

public:
	explicit CheckoutWidgetBis(Kommunikator *kom, QWidget *parent = 0);
    ~CheckoutWidgetBis();

signals:
	void sendPayer(KModelCart*);

private slots:
	void on_productsView_clicked(const QModelIndex &index);

	void on_pushButton_2_clicked();

private:
    Ui::CheckoutWidgetBis *ui;

	Kommunikator *kom_;

	KModelProduct *m_prod_;
	KModelCart *m_cart_;

	int price_;
};

#endif // CHECKOUTWIDGETBIS_H
