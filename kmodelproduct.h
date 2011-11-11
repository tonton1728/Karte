#ifndef KMODELPRODUCT_H
#define KMODELPRODUCT_H

#include <QAbstractListModel>
#include <QImage>
#include <QString>
#include <QList>

class Product : public QObject {
	Q_OBJECT

public:
    explicit Product( QObject *parent = 0, QString name = "", int price = 0, QImage picture = QImage(), QString script = "", int id=0);

public:
	inline QString name() { return name_; }
	inline int price() { return price_; }
	inline QImage picture() { return picture_; }
	inline QString script() { return script_; }
	inline int id() { return id_; }

public slots:
	void click();

signals:
	void clicked(Product* pro);
private:
	QString name_;
	int price_;
	QImage picture_;
	QString script_;
	int id_;
};

class KModelProduct : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KModelProduct(QObject *parent = 0);

	int rowCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
	QList<Product*> products_;
};

#endif // KMODELPRODUCT_H
