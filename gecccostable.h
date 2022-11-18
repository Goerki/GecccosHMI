#ifndef GECCCOSTABLE_H
#define GECCCOSTABLE_H

#include "gecccoselement.h"
#include <QMap>
#include <QList>
#include <QStandardItemModel>
#include <QStandardItem>


class GecccosTable : public GecccosElement
{
    QStandardItemModel* itemModel;
    QMap<QString, QList<QString>> table;
    QList<QStandardItem*> makeItemListFromStrinList(QList<QString> stringList, int column);
    void createModel();
public:
    GecccosTable(QString name, QString identifyer, QString description, bool mandatory);
    void addColumn(QString name, QString description);
    void setValueFromStream(QTextStream* stream);
    int rowCount();
    QStandardItemModel* getModel();
    void addEntryToTable();
    void changeItem(int row,int col, QString value);
    QString toString() override;

};

#endif // GECCCOSTABLE_H
