#include "user.h"

User::User(QObject *parent, QString firstname, QString lastname, QString email, QImage photo, QString tl1_domain, QString tl1_user, QString tl1_promotion, QString adhesion_type, QString adhesion_amount, QString adhesion_date, QList<QString> roles) : QObject(parent), firstname_(firstname), lastname_(lastname), email_(email), photo_(photo), tl1_domain_(tl1_domain), tl1_user_(tl1_user), tl1_promotion_(tl1_promotion), adhesion_type_(adhesion_type), adhesion_amount_(adhesion_amount), adhesion_date_(adhesion_date), roles_(roles)

{

}
