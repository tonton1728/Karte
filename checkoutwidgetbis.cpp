#include "checkoutwidgetbis.h"
#include "ui_checkoutwidgetbis.h"

CheckoutWidgetBis::CheckoutWidgetBis(Kommunikator *kom, QWidget *parent) :
    QWidget(parent),
	ui(new Ui::CheckoutWidgetBis),
	kom_(kom),
	price_(0)
{
    ui->setupUi(this);

	m_prod_ = new KModelProduct(kom_, this->parent());
	m_cart_ = new KModelCart(this->parent());

	ui->productsView->setModel(m_prod_);
	ui->cartView->setModel(m_cart_);
}

CheckoutWidgetBis::~CheckoutWidgetBis()
{
    delete ui;
}

void CheckoutWidgetBis::on_productsView_clicked(const QModelIndex &index)
{
	Product *p = m_prod_->productForIndex(index);
	m_cart_->addProduct(p);

	price_ += p->price();
	ui->total->setText(QString::number(price_ / 100.0) + QString::fromUtf8(" €"));
}

void CheckoutWidgetBis::on_pushButton_2_clicked()
{
	emit sendPayer(m_cart_);
}
