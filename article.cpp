#include "article.h"

Article::Article(QObject *parent,int id): QObject(parent)
{
    this->id = id;
}

void Article::click() {
    emit sendId(id);
}
