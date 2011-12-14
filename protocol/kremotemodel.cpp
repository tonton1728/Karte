#include "kremotemodel.h"

const QString KRemoteModel::modelName_ = "Void";

KRemoteModel::KRemoteModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
