#ifndef GECCCOSLIST_H
#define GECCCOSLIST_H

#include "gecccoselement.h"
#include <QStandardItemModel>
#include <QStandardItem>

class GecccosList : public GecccosElement
{
    QList<QString> elements;
    QStandardItemModel* itemModel;

public:
    GecccosList(QString name, QString identifyer, QString description, bool mandatory);
    void addStringToList(QString newElement);
    void setValueFromStream(QTextStream* stream);
    QStandardItemModel* getModel();
    void createModel();
    void addEntryToList();
    void changeItem(int number, QString value);
    QString toString() override;
    int getSize();

};

#endif // GECCCOSLIST_H
