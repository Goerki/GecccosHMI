#ifndef GECCCOSTREEITEM_H
#define GECCCOSTREEITEM_H
#include <QObject>
#include <QList>
#include <QVariant>
#include <QStandardItem>
#include <gecccosfile.h>


class GecccosTreeItem : QStandardItem
{
public:
    explicit GecccosTreeItem(QString name, QString description, int row, int parent,GecccosFile* fileVar);

       void appendChild(int childIndex);

       int child(int row) const;
       int childCount() const;
       int columnCount() const;
       QVariant data(int column) const;
       int parentItem() const;
       int getRow() const;
       GecccosFile* getFile() const;

private:
    QList<int> children;
    QString name;
    QString description;
    int parentIndex;
    int row;
    GecccosFile* file;


};

#endif // GECCCOSTREEITEM_H
