#include "gecccosfile.h"
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>


GecccosFile::GecccosFile(QString nameVar, QString descriptionVar)
{
    name = nameVar;
    description=descriptionVar;
    text ="";
}

void GecccosFile::addElementFromJsonObject(QJsonObject jsonObject, QString folder){
    QString elementName = jsonObject["name"].toString();
    QString elementType = jsonObject["type"].toString();
    QString elementID = jsonObject["identifyer"].toString();
    QString elementDescription = jsonObject["description"].toString();
    bool elementIsMandatory = jsonObject["mandatory"].toBool();

    GecccosElement::type type = GecccosElement::getTypeFromString(elementType);
    switch (type) {
    case GecccosElement::type::list:{
        GecccosList *list = new GecccosList(elementName, elementID, elementDescription, elementIsMandatory);
        listList.append(list);
    }
        break;
    case GecccosElement::type::parameter:{
        GecccosParameter* param = new GecccosParameter(elementName, elementID, elementDescription, elementIsMandatory);
        paramList.append(param);
    }
        break;
    case GecccosElement::type::map:{
        GecccosMap* map = new GecccosMap(elementName, elementID, elementDescription, elementIsMandatory);
        QJsonArray parameterArrayMap = jsonObject["parameter"].toArray();
        for (int i=0; i< parameterArrayMap.size(); i++){
            QJsonObject tempObject = parameterArrayMap[i].toObject();
            QString parameterName = tempObject["name"].toString();
            QString parameterID = tempObject["identifyer"].toString();
            QString parameterDescription = tempObject["description"].toString();
            bool parameterIsMandatory = tempObject["mandatory"].toBool();
            map->addParameter(parameterName, parameterID, parameterDescription, parameterIsMandatory);
        }
        mapList.append(map);
    }
        break;
    case GecccosElement::type::table:{
        GecccosTable* table = new GecccosTable(elementName, elementID, elementDescription, elementIsMandatory);
        QJsonArray parameterArrayTable = jsonObject["columns"].toArray();
        for (int i=0; i< parameterArrayTable.size(); i++){
            QJsonObject tempObject = parameterArrayTable[i].toObject();
            QString parameterName = tempObject["name"].toString();
            QString parameterDescription = tempObject["description"].toString();
            table->addColumn(parameterName, parameterDescription);
        }
        tableList.append(table);
    }
        break;
    case GecccosElement::type::poles:{
        QString poleDimensionFile = folder + "/"+ jsonObject["poleDimensionFile"].toString();
        QString poleStatesFile = folder + "/"+ jsonObject["poleStatesFile"].toString();
        QString prototype = jsonObject["prototype"].toString();
        bool isPrototype = false;
        if (prototype.toLower().contains("t")){
            isPrototype=true;
        }

        GecccosPoles* poles = new GecccosPoles(elementName, elementID, elementDescription,poleDimensionFile, poleStatesFile, isPrototype);
        polesList.append(poles);
    }
        break;
    default:
        break;
    }
}

bool GecccosFile::hasText(){
    return listList.isEmpty() && mapList.isEmpty() && paramList.isEmpty() && mapList.isEmpty();
}

void GecccosFile::getDataFromFolder(QString folderPath, QString folder){
    folderPath = folderPath.append("/");
    folderPath = folderPath.append(name);
    filePath = folderPath;

    QFile file(filePath);
    file.open(QIODevice::ReadWrite);
    QTextStream textStream(&file);
    QTextStream* streamPointer = &textStream;

    //go through all configured lists
    for (int elementIndex =0; elementIndex <listList.size(); elementIndex++ ){
        listList[elementIndex]->setValueFromStream(streamPointer);
        textStream.seek(0);
    }
    //go through all configured params
    for (int elementIndex =0; elementIndex <paramList.size(); elementIndex++ ){
        paramList[elementIndex]->setValueFromStream(streamPointer);
        textStream.seek(0);
    }
    //go through all configured maps
    for (int elementIndex =0; elementIndex <mapList.size(); elementIndex++ ){
        mapList[elementIndex]->setValueFromStream(streamPointer);
        textStream.seek(0);
    }
    //go through all configured tables
    for (int elementIndex =0; elementIndex <tableList.size(); elementIndex++ ){
        tableList[elementIndex]->setValueFromStream(streamPointer);
        textStream.seek(0);
    }
    //go through all configured poles
    for (int elementIndex =0; elementIndex <polesList.size(); elementIndex++ ){
        polesList[elementIndex]->setValueFromStream(streamPointer);
        textStream.seek(0);
    }

    if(hasText()){
        textStream.seek(0);
        text = textStream.readAll();
    }

    //get order of elements
    textStream.seek(0);
    this->setFileOrder(streamPointer);

}
void GecccosFile::setFileOrder(QTextStream* stream){
    while(!stream->atEnd()){
        QString line = stream->readLine();

        int sizeOfElementOrder=this->elementOrder.size();
        //check for all params
        for (int i=0; i<this->paramList.size(); i++){
            if (line.contains(this->paramList[i]->getIdentifyer())){
                this->elementOrder.append(paramList[i]);
            }
        }
        //check for all tables
        for (int i=0; i<this->tableList.size(); i++){
            if (line.contains(this->tableList[i]->getIdentifyer())){
                this->elementOrder.append(tableList[i]);
                for (int j=0; j< this->tableList[i]->rowCount(); j++){
                    stream->readLine();
                }
            }
        }
        //check for all poles
        for (int i=0; i<this->polesList.size(); i++){
            if (line.contains(this->polesList[i]->getIdentifyer())){
                GecccosComment* newComment = new GecccosComment(line);
                this->commentList.append(newComment);
                this->elementOrder.append(this->commentList[this->commentList.size()-1]);

                for (int j=0; j< this->polesList[i]->rowCount(); j++){
                    line = stream->readLine();
                    for (int i=0; i<this->paramList.size(); i++){
                        if (line.contains(this->paramList[i]->getIdentifyer())){
                            this->elementOrder.append(paramList[i]);
                            j--;
                        }
                    }
                }
                this->elementOrder.append(polesList[i]);
            }
        }
        //check for all maps
        for (int i=0; i<this->mapList.size(); i++){
            if (line.contains(this->mapList[i]->getIdentifyer())){
                this->elementOrder.append(mapList[i]);
                for (int j=0; j< this->mapList[i]->getSize(); j++){
                    stream->readLine();
                }
            }
        }
        //check for all lists
        for (int i=0; i<this->listList.size(); i++){
            if (line.contains(this->listList[i]->getIdentifyer())){
                this->elementOrder.append(listList[i]);
                for (int j=0; j <listList[i]->getSize(); j++ ){
                    stream->readLine();
                }
            }
        }
        if (sizeOfElementOrder==this->elementOrder.size()){
            //size did not change - saving line as comment
            GecccosComment* newComment = new GecccosComment(line);
            this->commentList.append(newComment);
            this->elementOrder.append(this->commentList[this->commentList.size()-1]);
        }
    }
    //ordering complete :)
    this->elementOrder.size();

}
QString GecccosFile::getName() const {return name;}
QString GecccosFile::getDescription() const {return description;}


int GecccosFile::getNumberLists(){
    return listList.size();

}

int GecccosFile::getNumberMaps(){
    return mapList.size();
}

int GecccosFile::getNumberParameters(){
    return paramList.size();
}

int GecccosFile::getNumberTables(){
    return tableList.size();
}

int GecccosFile::getNumberPoles(){
    return polesList.size();
}


GecccosList* GecccosFile::getList(int index){
    return listList[index];
}

GecccosMap* GecccosFile::getMap(int index){
    return mapList[index];
}

GecccosParameter* GecccosFile::getParam(int index){
    return paramList[index];
}

GecccosTable* GecccosFile::getTable(int index){
     return tableList[index];
}

GecccosPoles* GecccosFile::getPoles(int index){
     return polesList[index];
}

void GecccosFile::addParamEdit(QLineEdit* edit,GecccosParameter* parameter){
    paramLink[edit]=parameter;

}
GecccosParameter* GecccosFile::getParamForEdit(QLineEdit* edit){
    return paramLink[edit];
}

GecccosList* GecccosFile::activeList(){
    return listList[0];
}
GecccosTable* GecccosFile::activeTable(){
    return tableList[0];
}

GecccosPoles* GecccosFile::activePoles(){
    return polesList[0];
}

void GecccosFile::print(){
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream resetStream(&file);
    resetStream << "";
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    QTextStream stream(&file);
    if (hasText()){
        stream << this->text;
    } else {
        /*
    for (int i=0; i<listList.size(); i++){
        stream << listList[i]->toString();
        stream << "\n";
    }
    for (int i=0; i<mapList.size(); i++){
        stream << mapList[i]->toString();
        stream << "\n";
    }
    for (int i=0; i<paramList.size(); i++){
        stream << paramList[i]->toString();
        stream << "\n";
    }
    for (int i=0; i<tableList.size(); i++){
        stream << tableList[i]->toString();
        stream << "\n";
    }
    for (int i=0; i<polesList.size(); i++){
        stream << polesList[i]->toString();
        stream << "\n";
    }
    */
        for (int i=0; i<this->elementOrder.size(); i++){
            stream << this->elementOrder[i]->toString();
            stream << "\n";
        }
    }

}

QString GecccosFile::getText(){
    return text;
}


void GecccosFile::setText(QString text){
    this->text=text;
}




