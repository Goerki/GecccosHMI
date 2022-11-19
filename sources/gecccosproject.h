#ifndef GECCCOSPROJECT_H
#define GECCCOSPROJECT_H
#include <QString>
#include <gecccosfile.h>
#include <QList>
#include <QStandardItemModel>
#include "gecccoslogger.h"
#include "gecccostreeitem.h"

class GecccosProject {
    QString folder;
    QList<GecccosFile> inputFiles; //input row =0
    QList<GecccosFile> outputFiles; //output row=1
    QList<GecccosFile> workFiles; //work row=2

public:
    GecccosProject(
            QString folder,
            QString configFilePath,
            bool projectExists);
    GecccosLogger logger;
    QStandardItemModel* getStdModel();
    GecccosTreeItem* getItem(int index);
    void print();
    QString getFolder();

private:
    QJsonObject getObjectOfConfigFile(QString configFilePath);
    void addNewFile(QJsonObject object, QString type);
    void getValuesFromProject(QString folder);
    int addItem(QString name, QString description, int row, int parentIndex, GecccosFile* filePointer);
    QList<GecccosTreeItem> items;
    void setTreeItems();
    QStandardItemModel stdModel;
    void removeAllChildrenOfItem(QStandardItem* parent);




};

#endif // GECCCOSPROJECT_H
