#include "gecccosproject.h"
#include <QObject>
#include <QFile>
#include "QTextStream.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>


GecccosProject::GecccosProject(QString folder, QString configFilePath, bool projectExists)
{

    QJsonObject jsonObject;
    this->folder=folder;
    jsonObject = GecccosProject::getObjectOfConfigFile(configFilePath);
    QString logFile = jsonObject["logFile"].toString();
    QString logLevel = jsonObject["loglevel"].toString();
    GecccosLogger templogger=  GecccosLogger(logFile, logLevel);

    //create gecccos file object for each enty in the json file
    //start with input
    QJsonArray inputArray = jsonObject["input"].toArray();
    for(int i=0; i<inputArray.size();i++){
        this->addNewFile(inputArray[i].toObject(), "input");
    }
    QJsonArray outputArray = jsonObject["output"].toArray();
    for(int i=0; i<outputArray.size();i++){
        this->addNewFile(outputArray[i].toObject(), "output");
    }
    QJsonArray workArray = jsonObject["work"].toArray();
    for(int i=0; i<workArray.size();i++){
        this->addNewFile(workArray[i].toObject(), "work");
    }

    //Json completely loaded to gecccos objects
    //open project to get values

    if (projectExists){
        getValuesFromProject(folder);
    }
    // create all tree objects
    setTreeItems();
}


QString GecccosProject::getFolder(){
    return folder;
}


QJsonObject GecccosProject::getObjectOfConfigFile(QString configFilePath){
    QFile configFile(configFilePath);
    if(!configFile.open(QIODevice::ReadOnly)){
        //file not opened correctly
        std::cout << "file not opened correctly";
        exit(0);
    }
    QTextStream textStream(&configFile);
    QString fullString = textStream.readAll();


    configFile.close();

    QByteArray json_bytes = fullString.toLocal8Bit();

    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()){
        //file not loaded correctly
        std::cout << "file not loaded correctly";
        exit(0);
    }
    QJsonObject obj = json_doc.object();
    return json_doc.object();

}

void GecccosProject::addNewFile(QJsonObject object, QString type){
    if (object.isEmpty() || type.isEmpty()){
        return;
    }

    QString fileName = object["filename"].toString();
    QString description = object["description"].toString();
    GecccosFile newFile = GecccosFile(fileName, description);
    QJsonArray contentArray = object["content"].toArray();
    for(int i = 0; i< contentArray.size(); i++){
        newFile.addElementFromJsonObject(contentArray[i].toObject(),folder);
    }

    if (type.contains("input")){
        inputFiles.append(newFile);
    } else if(type.contains("output")){
        outputFiles.append(newFile);
    } else if(type.contains("work")){
        workFiles.append(newFile);
    }


}

void GecccosProject::getValuesFromProject(QString folder){
    //inputFiles
    QString workingFolder = folder+"/input";

    for (int i=0; i<inputFiles.size();i++){
        inputFiles[i].getDataFromFolder(workingFolder, folder);

    }

    //output files
    workingFolder = folder+"/output";

    for (int i=0; i<outputFiles.size();i++){
        outputFiles[i].getDataFromFolder(workingFolder, folder);

    }

    //work files
    workingFolder = folder+"/work";

    for (int i=0; i<workFiles.size();i++){
        workFiles[i].getDataFromFolder(workingFolder, folder);

    }
}

int GecccosProject::addItem(QString name, QString description,int row,  int parentIndex, GecccosFile* filePointer){
    GecccosTreeItem newItem = GecccosTreeItem(name, description,row,  parentIndex, filePointer);
    items.append(newItem);
    if (parentIndex >= 0){
        items[parentIndex].appendChild(items.size()-1);
    }
    return items.size()-1;

}

GecccosTreeItem* GecccosProject::getItem(int index){
    return &items[index];
}

void GecccosProject::setTreeItems(){

    //input
    int rootItem = addItem("name", "description", 0, -1, nullptr);

    int inputBase = addItem("input", "all files used for the input",0, rootItem, nullptr);
    for (int inputIndex=0; inputIndex < inputFiles.size(); inputIndex++){
       addItem(inputFiles[inputIndex].getName(), inputFiles[inputIndex].getDescription(),inputIndex, inputBase, &inputFiles[inputIndex]);
    }

    //output
    int outputBase = addItem("output", "all files used for the output",1, rootItem, nullptr);
    for (int outputIndex=0; outputIndex < outputFiles.size(); outputIndex++){
       addItem(outputFiles[outputIndex].getName(), outputFiles[outputIndex].getDescription(),outputIndex, outputBase, &outputFiles[outputIndex]);
    }

    //work
    int workBase = addItem("work", "all files used for the work section",2, rootItem, nullptr);
    for (int workIndex=0; workIndex < workFiles.size(); workIndex++){
       addItem(workFiles[workIndex].getName(), workFiles[workIndex].getDescription(),workIndex, workBase,&workFiles[workIndex] );
    }


    //creating StandardModel

    //layer0
    QList<QStandardItem*> columnList;
    for (int layer0Increment=0; layer0Increment<items[0].childCount(); layer0Increment++ ){
        int layer0Index = items[0].child(layer0Increment);

        QStandardItem* newStdRowItemLayer0 = new QStandardItem(layer0Increment,1);
        removeAllChildrenOfItem(newStdRowItemLayer0);
        newStdRowItemLayer0->setData(items[layer0Index].data(0),0);
        newStdRowItemLayer0->setData(layer0Index,1);
        newStdRowItemLayer0->setToolTip(items[layer0Index].data(1).toString());



        QStandardItem* newStdColItemLayer0 = new QStandardItem(layer0Increment,2);
        removeAllChildrenOfItem(newStdColItemLayer0);
        newStdColItemLayer0->setData(items[layer0Index].data(1),0);
        newStdColItemLayer0->setToolTip(items[layer0Index].data(1).toString());
        newStdColItemLayer0->setData(layer0Index,1);


        //layer1
        QList<QStandardItem*> colList;
        for (int layer1Increment=0; layer1Increment<items[layer0Index].childCount(); layer1Increment++ ){
            int layer1Index = items[layer0Index].child(layer1Increment);
            QStandardItem* newStdRowItemLayer1 = new QStandardItem(layer1Increment,1);
            removeAllChildrenOfItem(newStdRowItemLayer1);
            newStdRowItemLayer1->setData(items[layer1Index].data(0),0);
            newStdRowItemLayer1->setData(layer1Index,1);
            newStdRowItemLayer1->setToolTip(items[layer1Index].data(1).toString());


            QStandardItem* newStdColItemLayer1 = new QStandardItem(layer1Increment,2);
            removeAllChildrenOfItem(newStdColItemLayer1);
            newStdColItemLayer1->setData(items[layer1Index].data(1),0);
            newStdColItemLayer1->setToolTip(items[layer1Index].data(1).toString());
            newStdColItemLayer1->setData(layer1Index,1);


            colList.append(newStdColItemLayer1);
            newStdRowItemLayer0->insertRow(layer1Increment,newStdRowItemLayer1);
        }
        if (colList.size()> 0){
            newStdRowItemLayer0->insertColumn(1,colList);
        }



        columnList.append(newStdColItemLayer0);
        stdModel.invisibleRootItem()->insertRow(layer0Increment, newStdRowItemLayer0);


    }
    stdModel.invisibleRootItem()->insertColumn(1, columnList);

    /*

    QStandardItem* newStdItem = new QStandardItem(0,1);
    newStdItem->setData("name",0);

    QStandardItem* newStdItemDescr = new QStandardItem(0,2);
    newStdItemDescr->setData("description",0);
    QList<QStandardItem*> list;
    list.append(newStdItemDescr);


    stdModel.invisibleRootItem()->insertRow(1, newStdItem);
    stdModel.invisibleRootItem()->insertColumn(1, list);
    //return items.size()-1;

    */
    //stdModel.invisibleRootItem()->setColumnCount(2);
    QStringList labels;
    labels.append("name");
    labels.append("description");
    stdModel.setHorizontalHeaderLabels(labels);

}
void GecccosProject::removeAllChildrenOfItem(QStandardItem* parent){
    if (parent->hasChildren()){
        parent->removeColumn(0);
        parent->removeRow(0);
    }
    return;

}

QStandardItemModel* GecccosProject::getStdModel(){
    return &stdModel;
}


void GecccosProject::print(){
    for (int i=0; i<inputFiles.size();i++){
        inputFiles[i].print();
    }
    for (int i=0; i<outputFiles.size();i++){
        outputFiles[i].print();
    }
    for (int i=0; i<workFiles.size();i++){
        workFiles[i].print();
    }
}



