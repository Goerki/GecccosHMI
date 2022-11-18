#include "gecccosparameter.h"


GecccosParameter::GecccosParameter(QString name, QString identifyer, QString description, bool mandatory)
{
    this->name = name;
    this->description=description;
    this->mandatory = mandatory;
    this->identifyer=identifyer;
}


void GecccosParameter::setValueFromStream(QTextStream* streamPointer) {

    while(!streamPointer->atEnd()){
        QString line = streamPointer->readLine();
        if ( !line.contains("#") && line.contains(identifyer)){
            QStringList splitString = line.split(" ",Qt::SkipEmptyParts);
            value= splitString[1];
            return;
        }
    }
    //identifyer was not found
}

void GecccosParameter::setValueFromStringList(QStringList string){
    for (int i=0; i<string.size(); i++){
    if ( !string[i].contains("#") && string[i].contains(identifyer)){
        QStringList splitString = string[i].split(" ",Qt::SkipEmptyParts);
        value= splitString[1];
        return;
        }
    }
    //identifyer was not found
}

QString GecccosParameter::getValue(){
    return value;
}

void GecccosParameter::setValue(QString text){
    value=text;
}

QString GecccosParameter::toString(){
    QString result;
    result += identifyer;
    result += "    ";
    result += value;
    return result;

}


