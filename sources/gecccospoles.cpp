#include "gecccospoles.h"

GecccosPoles::GecccosPoles(QString name, QString identifyer, QString description, QString poleDimensionFile, QString statesFile, bool isPrototype)
{
    this->name = name;
    this->description=description;
    this->poleDimensionFile = poleDimensionFile;
    this->identifyer=identifyer;
    itemModel= new QStandardItemModel();
    this->states = GecccosStates(statesFile);
    this->isPrototype=isPrototype;

    QFile dimensionFile(poleDimensionFile);
    if(!dimensionFile.open(QIODevice::ReadOnly)){
        //file not opened correctly
        std::cout << "file not opened correctly";
        exit(0);
    }
    QTextStream* textStream = new QTextStream(&dimensionFile);
    bool valuesReached=false;
    while(!textStream->atEnd()){
        QString line = textStream->readLine();
        if (valuesReached&&line.split(" ",Qt::SkipEmptyParts).size() > 1){
            PoleDimensions newDimension = PoleDimensions(line);
            this->poleDimensions.append(newDimension);
        }
        if (line.contains("---")){
            valuesReached=true;
        }
    }

}


void GecccosPoles::createModel(){

}

void GecccosPoles::setValueFromStream(QTextStream* stream){

    QStringList filePart;
    bool identifyerFound = false;
    bool paramsReached = false;
    QList<QString> columns;
    columns.append("J");
    columns.append("pi");
    columns.append("E_pole");
    stream->seek(0);
    QList<int> columnOrder;
    while(!stream->atEnd()){
        QString line = stream->readLine();

        if (line.contains(identifyer)){
            //identifyier found - search for each member of the map
            identifyerFound = true;
        }
        if (identifyerFound){
            if (line.startsWith("#")){
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


        if (columnOrder.size()>0 && line.split(" ",Qt::SkipEmptyParts ).size()>= columns.size() && !line.startsWith("#")){
            QStringList splitLine = line.split(" ",Qt::SkipEmptyParts);
            int j=splitLine[columnOrder[0]].toInt();
            bool isPositive=splitLine[columnOrder[1]].toInt()>=0;
            GecccosPole *newPole= new GecccosPole(getDimensionForPole(j,isPositive), this->isPrototype);
            newPole->j=j;
            newPole->isPositive=isPositive;
            newPole->energy=splitLine[columnOrder[2]].toFloat();
            bool variationReached=false;

            for (int i=3; i<splitLine.size();i++){
                if (splitLine[i].contains("F")){
                    variationReached=true;
                    newPole->variationEnabled=false;

                } else  if (splitLine[i].contains("T")){
                    variationReached=true;
                    newPole->variationEnabled=true;
                } else if (variationReached) {
                    QString part= splitLine[i];
                    QString trimmedPart= splitLine[i].trimmed();
                    if (splitLine[i].trimmed().startsWith("#")){
                        //append remaining line to comment section
                        newPole->comment=line.mid(line.indexOf("#"),-1);
                        break;

                    } else {
                    int widthIndex = i-5-newPole->numberWidths;
                    QString variation = splitLine[i];
                    if (widthIndex==-1){
                        newPole->energyVariation=splitLine[i].toDouble();
                    } else if (widthIndex < 0){
                        newPole->comment= "whaaaaaaaaAAAAaaaAAATTTT???";
                    } else if (newPole->widths.size()>widthIndex){
                        newPole->widths[widthIndex].variation=splitLine[i].toDouble();
                    }

                    }
                } else {
                newPole->widths.append(states.getWidthFor(j,isPositive, i-3, splitLine[i].toFloat()));
                }
            }
            poles.append(*newPole);

        }
    }
    this->setMaxNumberWidths();
}

void GecccosPoles::setMaxNumberWidths(){
    maxNumberWidths =0;
    for (int i=0; i<poles.size(); i++){
        if (poles[i].numberWidths>maxNumberWidths){
            maxNumberWidths=poles[i].numberWidths;
        }
    }
}

int GecccosPoles::rowCount(){
    return this->poles.size();

}

QStandardItemModel* GecccosPoles::getModel(){
    this->setMaxNumberWidths();
    this->itemModel = new QStandardItemModel();
    QStringList labels;
    labels.append("J");
    labels.append("parity");
    labels.append("energy");
    labels.append("energyVariation");
    labels.append("numberwidths");
    labels.append("variation enabled?");
    labels.append("comment");
    for (int i=0; i<maxNumberWidths; i++){
        labels.append("width " + QVariant(i).toString());
    }


    //first row - create new columns
    if (this->poles.size()>0){
    QList<QStandardItem*> itemList = makeItemListForPole(0);
    this->itemModel->invisibleRootItem()->appendRow(itemList);

        for (int i=1; i<poles.size(); i++){
            QList<QStandardItem*> itemList = makeItemListForPole(i);
            this->itemModel->invisibleRootItem()->appendRow(itemList);

        }
    }
    this->itemModel->setHorizontalHeaderLabels(labels);

    int colCount= this->itemModel->columnCount();
    return this->itemModel;
}

QList<QStandardItem*> GecccosPoles::makeItemListForPole(int poleIndex){
    QList<QStandardItem*> result;
    //j
    QStandardItem *jItem = new QStandardItem(poleIndex,0);
    QString jData;
    if (poles[poleIndex].isPositive){
        jData = "+"+ QString::number(poles[poleIndex].j) + "/2";
    }else {
        jData = "-"+ QString::number(poles[poleIndex].j) + "/2";
    }

    jItem->setData(jData, 0);
    jItem->setEditable(false);
    jItem->setSelectable(false);
    jItem->setToolTip("J Total");

    result.append(jItem);

    //parity
    QStandardItem *parityItem = new QStandardItem(poleIndex,1);
    if (poles[poleIndex].isPositive){
        parityItem->setData(1,0);
    } else {
        parityItem->setData(-1,0);
    }
    parityItem->setEditable(false);
    parityItem->setSelectable(false);
    parityItem->setToolTip("Parity");
    result.append(parityItem);


    //energy
    QStandardItem *energyItem = new QStandardItem(poleIndex,2);
    energyItem->setData(poles[poleIndex].energy,0);
    energyItem->setEditable(true);
    result.append(energyItem);

    //energyvariation
    QStandardItem *energyVariationItem = new QStandardItem(poleIndex,3);
    energyVariationItem->setData(poles[poleIndex].energyVariation,0);
    if(this->isPrototype){
        energyVariationItem->setEditable(true);
    }else {
        energyVariationItem->setEditable(false);
        energyVariationItem->setSelectable(false);
    }

    result.append(energyVariationItem);




    //numberWidths
    QStandardItem *widthsItem = new QStandardItem(poleIndex,4);
    widthsItem->setData(poles[poleIndex].numberWidths,0);
    widthsItem->setEditable(false);
    result.append(widthsItem);


    //variationEnabled
    QStandardItem *variationEnabledItem = new QStandardItem(poleIndex,5);
    variationEnabledItem->setCheckable(true);
    if (this->isPrototype){
        variationEnabledItem->setEnabled(true);
        if (poles[poleIndex].variationEnabled){
            variationEnabledItem->setCheckState(Qt::Checked);
        }else {
            variationEnabledItem->setCheckState(Qt::Unchecked);
        }
    }else {
        variationEnabledItem->setEnabled(false);
        variationEnabledItem->setCheckState(Qt::Unchecked);
        variationEnabledItem->setToolTip("This setting can only be enabled when prototype is set to true in the config");
    }



    result.append(variationEnabledItem);



    //Comment
    QStandardItem *commentsItem = new QStandardItem(poleIndex,6);

    if (this->isPrototype){
        commentsItem->setData(poles[poleIndex].getComment(),0);
        commentsItem->setEditable(true);
        commentsItem->setSelectable(true);

    }else {
        commentsItem->setData("",0);
        commentsItem->setEditable(false);
        commentsItem->setSelectable(false);
        commentsItem->setToolTip("This setting can only be edited when prototype is set to true in the config");
    }
    result.append(commentsItem);


    //entries
    for (int i=0; i< poles[poleIndex].numberWidths; i++){
        QStandardItem *newItem = new QStandardItem(poleIndex,i+7);
        newItem->setData(poles[poleIndex].widths[i].value,0);
        newItem->setEditable(false);
        result.append(newItem);

    }

    //empty entries
    for (int i=poles[poleIndex].numberWidths; i<maxNumberWidths;i++){
        QStandardItem *newItem = new QStandardItem(0,i);
        newItem->setData("",0);
        newItem->setEditable(false);
        newItem->setEnabled(false);
        newItem->setBackground(QBrush(Qt::gray));
        result.append(newItem);
    }

    return result;

}


void GecccosPoles::addEntryToTable(QString j){
    bool parity = !j.contains("-");
    QString number = j.split("/",Qt::SkipEmptyParts)[0].remove(0,1);
    int jTot=number.toInt();
    if (!parity){
        jTot=jTot*-1;
    }
    GecccosPole newPole(getDimensionForPole(number.toInt(), parity), this->isPrototype);
    for (int i=0; i<getDimensionForPole(number.toInt(), parity); i++){
        newPole.widths.append(states.getWidthFor(jTot,parity,i, 0.0));
    }
    newPole.energy=0.0;
    newPole.j=number.toInt();
    newPole.isPositive=parity;
    poles.append(newPole);
}

void GecccosPoles::changeItem(int row,int col, QString value){
    //you can only change the comment(col 7), the energy (col 2), the energy variation (col 3) or the varation enabled flag (index 6)
    if (col==6){
        if (!value.startsWith("#")){
            value = "#" + value;
        }
        this->poles[row].comment=value;
    }
    if (col==5){
        this->poles[row].setVariationEnabled(value);
    }
    if (col==3){
        this->poles[row].energyVariation= value.toDouble();
    }
    if (col==2){
        this->poles[row].energy=  value.toDouble();
    }


}

QString GecccosPoles::toString(){
    QString resultString="";
    for (int i=0; i<this->poles.size(); i++){
        resultString+=poles[i].toString()+"\n";
    }
    return resultString;
}

int GecccosPoles::getDimensionForPole(int j, bool isPositive){
    for (int i=0; i<poleDimensions.size();i++){
        if (poleDimensions[i].getJ()==j && poleDimensions[i].isPositive()==isPositive){
            return poleDimensions[i].getNumberWidths();
        }

    }
    return 0;
}

QStringList GecccosPoles::getAvailableConfigurations(){
    QStringList newList;
    for (int i=0; i<poleDimensions.size(); i++){
        QString descr = "";
        if (poleDimensions[i].isPositive()){
            descr="+";
        } else {
            descr="-";
        }
        descr.append(QVariant(poleDimensions[i].getJ()).toString());
        descr+="/2";
        newList.append(descr);
    }
    return newList;

}

GecccosPoleWidth* GecccosPoles::getPoleForIndex(const QModelIndex index){
    int row=index.row();
    int column=index.column();
    if (column>=6){
        return this->poles[row].getWidthOfIndex(column);
    }
    return nullptr;


}

bool GecccosPoles::getIsPrototype(){
    return this->isPrototype;
}
