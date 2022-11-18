#include "gecccostable.h"

GecccosTable::GecccosTable(QString name, QString identifyer, QString description, bool mandatory)
{
    this->name = name;
    this->description=description;
    this->mandatory = mandatory;
    this->identifyer=identifyer;
    itemModel = new QStandardItemModel();
}


void GecccosTable::addColumn(QString name, QString description){
    QList<QString> newList;
    newList.append(description);
    table.insert(name, newList);

}



void GecccosTable::setValueFromStream(QTextStream* stream) {


    QStringList filePart;
    bool identifyerFound = false;
    bool paramsReached = false;
    QList<QString> columns = table.keys();
    stream->seek(0);
    QList<int> columnOrder;
    while(!stream->atEnd()){
        QString line = stream->readLine();

        if (line.contains(identifyer)){
            //identifyier found - search for each member of the map
            identifyerFound = true;
        }
        if (identifyerFound){
            if (line.contains("#")){
                //look for keys
                bool colContained = true;
                for (int columnIndex = 0; columnIndex < columns.size(); columnIndex++){
                    QString column= columns[columnIndex];


                    if (!line.contains(columns[columnIndex])){
                        colContained = false;
                        break;
                    }
                }
                if (colContained && columns.size()>0){
                    QStringList splitLine = line.split(" ",Qt::SkipEmptyParts);
                    if (splitLine.size()<= 1){
                        splitLine = line.split("\t",Qt::SkipEmptyParts);
                    }
                    for (int columnIndex = 0; columnIndex < columns.size(); columnIndex++){
                        for (int splitIndex=0; splitIndex < splitLine.size(); splitIndex++){
                            if (splitLine[splitIndex].contains(columns[columnIndex])){
                                columnOrder.append(splitIndex);
                            }
                        }
                    }
                }

            } else {
                //append otherwise
                filePart.append(line);
                paramsReached = true;
            }
        }
    }
    //filepart was extracted - initialize parameter

    //get order of columns



    for (int lineIndex=0; lineIndex<filePart.size(); lineIndex++){
        QString line = filePart[lineIndex];

        if (columnOrder.size()>0 && line.split(" ",Qt::SkipEmptyParts ).size()>= columns.size() && !line.contains("#")){
            QStringList splitLine = line.split(" ",Qt::SkipEmptyParts);
            for (int i=0; i<columnOrder.size();i++){
                table[columns[i]].append(splitLine[columnOrder[i]]);
            }
        }
    }
}



QStandardItemModel* GecccosTable::getModel(){
    itemModel = new QStandardItemModel();
    QStringList labels;
    QList<QString> keyList = table.keys();
    //first column - create row for each entry

    QList<QStandardItem*> itemList = makeItemListFromStrinList(table[keyList[0]], 0);
    for (int i=0; i<itemList.size(); i++){
        itemModel->invisibleRootItem()->appendRow(itemList[i]);
    }
    labels.append(keyList[0]);
    for (int i=1; i<keyList.size(); i++){
        labels.append(keyList[i]);
        QList<QStandardItem*> itemList = makeItemListFromStrinList(table[keyList[i]], i);
        itemModel->invisibleRootItem()->appendColumn(itemList);
    }
    itemModel->setHorizontalHeaderLabels(labels);


    return itemModel;
}

QList<QStandardItem*> GecccosTable::makeItemListFromStrinList(QList<QString> stringList, int column){
    QList<QStandardItem*> result;

    for(int i=0; i<stringList.size(); i++){
        QStandardItem *newItem = new QStandardItem(i, column);
        newItem->setData(stringList[i],0);
        result.append(newItem);
    }
    return result;

}

void GecccosTable::createModel(){

}

void GecccosTable::addEntryToTable(){
    for (int i=0; i<table.keys().size(); i++){
        table[table.keys()[i]].append("");
    }
}

void GecccosTable::changeItem(int row,int col, QString value){
    QString key = table.keys()[col];
    table[key][row]=value;
}

QString GecccosTable::toString(){
    QString result ="#";
    for (int i=0; i < table.keys().size(); i++){
        result += table.keys()[i];
        result+= " \t";
    }
    result=result.trimmed();
    result += " \n";
    for (int row=1; row< rowCount(); row ++){
        for (int col=0; col<table.keys().size(); col++){
            result+= " \t";
            result += table[table.keys()[col]][row];
        }
        result +=" \n";
    }
    result=result.trimmed();
    return result;
}

int GecccosTable::rowCount(){
    return table[table.keys()[0]].size();
}

