#include "gecccoselement.h"



GecccosElement::type GecccosElement::getTypeFromString(QString string){
    if (string.contains("parameter")){
        return GecccosElement::type::parameter;
    }
    if (string.contains("table")){
        return GecccosElement::type::table;
    }
    if (string.contains("list")){
        return GecccosElement::type::list;
    }
    if (string.contains("map")){
        return GecccosElement::type::map;
    }
    if (string.contains("poles")){
        return GecccosElement::type::poles;
    }
}

    void GecccosElement::setValueFromStream(QTextStream* stream){
        //this should not be called at all
    }

    QString GecccosElement::getName(){
        return name;
    }


    QString GecccosElement::toString(){
        return "";
    }
    QString GecccosElement::getIdentifyer(){
        return this->identifyer;
    }

    QString GecccosElement::getDescription(){
        return this->description;
    }
