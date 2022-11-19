#include "gecccostreeitem.h"

GecccosTreeItem::GecccosTreeItem(QString nameVar, QString descriptionVar, int row, int parentVar,GecccosFile* fileVar
                                 )
{
    name=nameVar;
    description=descriptionVar;
    parentIndex=parentVar;
    this->row = row;
    this->file=fileVar;

}

GecccosFile* GecccosTreeItem::getFile() const{
    return file;
}

void GecccosTreeItem::appendChild(int childIndex){
    children.append(childIndex);
}

int  GecccosTreeItem::child(int row) const{
    return children[row];
                              }


int GecccosTreeItem::childCount() const{
    return children.size();
}


int GecccosTreeItem::columnCount() const{
    return 2;
}

QVariant GecccosTreeItem::data(int column) const{
    if (column==0){
        return name;
    }else {
        return description;
    }
    return "";
}

int GecccosTreeItem::parentItem() const{
    return parentIndex;
}
int GecccosTreeItem::getRow() const{
    return row;
}

