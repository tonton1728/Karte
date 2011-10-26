#ifndef ARTICLE_H
#define ARTICLE_H
#include <QObject>

class Article : public QObject
{
    Q_OBJECT
public:
    Article(QObject *parent = 0 ,int id=0);
    int id;
public slots:
    void click();
signals:
    void sendId(int id);
};

#endif // ARTICLE_H
