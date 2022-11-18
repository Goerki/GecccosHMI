#include "gecccosmap.h"

GecccosMap::GecccosMap(QString name, QString identifyer, QString description, bool mandatory)
{
    this->name = name;
    this->description=description;
    this->mandatory = mandatory;
    this->identifyer=identifyer;
}


void GecccosMap::addParameter(QString name, QString identifyer, QString description, bool mandatory){
    GecccosParameter newParameter = GecccosParameter(name, identifyer, description, mandatory);
    map.append(newParameter);
}


void GecccosMap::setValueFromStream(QTextStream* stream) {


    QStringList filePart;
    bool identifyerFound = false;
    bool paramsReached = false;

    while(!stream->atEnd()){
        QString line = stream->readLine();

        if (identifyerFound){
            if (!line.contains("#")){
                filePart.append(line);
                paramsReached = true;
            }
            if (paramsReached && line.contains("#")){
                break;
            }
    }
        if (line.contains(identifyer)){
            //identifyier found - search for each member of the map
            identifyerFound = true;
            this->identifyer=line;
        }
    }

    //filepart was extracted - initialize parameter
    for (int paramIndex=0; paramIndex<map.size(); paramIndex++){
        map[paramIndex].setValueFromStringList(filePart);
    }

    this->getName();


}

QString GecccosMap::getName(){
    return name;
}
int GecccosMap::getSize(){
    return map.size();
}

GecccosParameter* GecccosMap::getParam(int index){
    return &map[index];
}

QString GecccosMap::toString(){
    QString result =this->getIdentifyer()+"\n";
    for (int i=0; i<this->map.size(); i++){
        result.append(this->map[i].toString()+"\n");
    }
    return result;
}



