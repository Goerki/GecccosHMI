#include "gecccoslist.h"

GecccosList::GecccosList(QString name, QString identifyer, QString description, bool mandatory)
{
    this->name = name;
    this->description=description;
    this->mandatory = mandatory;
    this->identifyer=identifyer;
}


void GecccosList::addStringToList(QString newElement){
    elements.append(newElement);
    itemModel = new QStandardItemModel();


}


void GecccosList::setValueFromStream(QTextStream* stream) {


    QStringList filePart;
    bool identifyerFound = false;
    bool paramsReached = false;

    while(!stream->atEnd()){
        QString line = stream->readLine();

        if (line.contains(identifyer)){
            //identifyier found - search for each member of the map
            identifyerFound = true;
        }
        if (identifyerFound){
            if (!line.contains("#")){
                filePart.append(line);
                paramsReached = true;
            }
            if (paramsReached && line.contains("#")){
                break;
            }
    }
    }

    //filepart was extracted - initialize parameter
    for (int lineIndex=0; lineIndex<filePart.size(); lineIndex++){
        addStringToList(filePart[lineIndex].trimmed());
    }
}
QStandardItemModel* GecccosList::getModel(){
    createModel();
    QStringList labels;
    labels.append("values");
    itemModel->setHorizontalHeaderLabels(labels);
    return itemModel;
}

void GecccosList::createModel(){
    itemModel = new QStandardItemModel();
    QStandardItemModel pointer;
    //connect(addRowButton, &QPushButton::clicked, this, MainWindow::addRowToActiveList);

    QList<QStandardItem*> list;
    for (int i=0; i<elements.size(); i++){
        QStandardItem* newItem = new QStandardItem();
        newItem->setData(elements[i], 0);

        list.append(newItem);
    }
    itemModel->invisibleRootItem()->insertRows(0,list);

}

void GecccosList::addEntryToList(){
    elements.append("");
}




void GecccosList::changeItem(int number, QString value){
    elements[number] = value;
}

QString GecccosList::toString(){
    QString result;
    for (int i=0; i<elements.size(); i++){
        result+=elements[i];
        result+="\n";
    }
    result=result.trimmed();
    return result;
}
int GecccosList::getSize(){
    return this->elements.size();
}
