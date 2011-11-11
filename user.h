#ifndef USER_H
#define USER_H

#include <QObject>
#include <QImage>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = 0, QString firstname = QString(), QString lastname = QString(),QString email = QString(), QImage photo = QImage(), QString tl1_domain = QString(), QString tl1_user = QString(), QString tl1_promotion = QString(), QString adhesion_type = QString(), QString adhesion_amount = QString(), QString adhesion_date = QString(), QList<QString> roles = QList<QString>());


    inline QString firstname() {return this->firstname_;}
    inline QString lastname() {return this->lastname_;}
    inline QString email() {return this->email_;}
    inline QImage photo() {return this->photo_;}
    inline QString tl1_domain() {return this->tl1_domain_;}
    inline QString tl1_user() {return this->tl1_user_;}
    inline QString tl1_promotion() {return this->tl1_promotion_;}
    inline QString adhesion_type() {return this->adhesion_type_;}
    inline QString adhesion_amount() {return this->adhesion_amount_;}
    inline QString adhesion_date() {return this->adhesion_date_;}
    inline QList<QString> roles() {return this->roles_;}

signals:

public slots:


private:
     QString firstname_;
     QString lastname_;
     QString email_;
     QImage photo_;
     QString tl1_domain_;
     QString tl1_user_;
     QString tl1_promotion_;
     QString adhesion_type_;
     QString adhesion_amount_;
     QString adhesion_date_;
     QList<QString> roles_;
};

#endif // USER_H
