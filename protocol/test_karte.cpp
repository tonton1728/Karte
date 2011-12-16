#include <QApplication>
#include <QString>
#include <QDebug>
#include <QTableView>

#include "kommunikator.h"
#include "kwery.h"
#include "kremotemodel.h"

/*class Receiver : public QObject {
	Q_OBJECT

public slots:
	void displayLine(QString line) {
		qDebug() << line;
	}

	void displayJson(QVariant js) {
		qDebug() << js;
	}
};*/

class KomTest : public QObject {
	Q_OBJECT

private:
	Kommunikator kom;
	KRemoteModel rm;
	enum State {
		Idle, Connecting, Authenticating
	};
	State s;

public:
	KomTest() : kom(), rm(&kom), s(Idle) {
		connect(&kom, SIGNAL(stateChanged(Kommunikator::KonnState)), this, SLOT(komStateChange(Kommunikator::KonnState)));
		connect(&rm, SIGNAL(stateChanged(KRemoteModel::ModelState)), this, SLOT(modelStateChange(KRemoteModel::ModelState)));

		setState(Connecting);
	}

	QAbstractListModel *model() { return &rm; }

private:
	void setState(State s) {
		this->s = s;

		switch(s) {
		case Connecting:
			kom.konnect("loc.telnet-tl1.org", 8000, false);
			break;
		case Authenticating:
			kom.authCheckout(42);
			break;
		default:
			/* prison */ break;
		}
	}

private slots:
	void komStateChange(Kommunikator::KonnState st) {
		qDebug() << "New Kom State:" << st;

		if(st == Kommunikator::Established) {
			if(s == Connecting) {
				setState(Authenticating);
			}
		}
	}

	void modelStateChange(KRemoteModel::ModelState st) {
		if(st == KRemoteModel::Complete) {
			QModelIndex idx = rm.index(0, 0);
			qDebug() << rm.headerData(0, Qt::Horizontal, Qt::DisplayRole);
			qDebug() << rm.data(idx, Qt::DisplayRole);
		}
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	KomTest tst;
	QTableView tv;

	tv.setModel(tst.model());
	tv.show();

	return app.exec();
}

#include "test_karte.moc"
