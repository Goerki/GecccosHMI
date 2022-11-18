#ifndef GECCCOSPOLES_H
#define GECCCOSPOLES_H

#include "gecccoselement.h"
#include "gecccospole.h"
#include "gecccospolewidth.h"
#include <QMap>
#include <QList>
#include "QStringList"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFile>
#include <iostream>
#include "poledimensions.h"
#include "gecccosstates.h"


class GecccosPoles : public GecccosElement
{
    QStandardItemModel* itemModel;
    QList<GecccosPole> poles;
    QList<QStandardItem*> makeItemListForPole( int poleIndex);
    QString poleDimensionFile;
    int maxNumberWidths;
    GecccosStates states;

public:
    GecccosPoles(QString name, QString identifyer, QString description, QString poleDimensionFile, QString statesFile);
    void createModel();
    void setValueFromStream(QTextStream* stream);
    int rowCount();
    QStandardItemModel* getModel();
    void addEntryToTable();
    void changeItem(int row,int col, QString value);
    QString toString() override;
    QStringList getAvailableConfigurations();
    void addEntryToTable(QString j);
    GecccosPoleWidth* getPoleForIndex(const QModelIndex index);
private:
    QList<PoleDimensions> poleDimensions;
    int getDimensionForPole(int j, bool isPositive);
    void setMaxNumberWidths();

};

#endif // GECCCOSPOLES_H
