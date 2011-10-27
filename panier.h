#ifndef PANIER_H
#define PANIER_H

#include <QString>

class panier
{
public:
    panier(QString des = "", float price = 0);
private:
    QString des;
    float price;
};

#endif // PANIER_H
