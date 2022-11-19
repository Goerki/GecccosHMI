#include "gecccospole.h"

GecccosPole::GecccosPole(int numberWidths, bool prototype)
{
    this->numberWidths=numberWidths;
    energyVariation=0.0;
    this->variationEnabled=false;
    this->isPrototype=prototype;
}

double GecccosPole::getValue(int index){
    return widths[index].getValue();
}

GecccosPoleWidth* GecccosPole::getWidthOfIndex(int index){
    if (index>=7 && index-7 < this->widths.size()){
        return &(this->widths[index-7]);
       }
    return nullptr;
}
QString GecccosPole::getComment(){
    return this->comment;
}

QString GecccosPole::toString(){
    QString line = "";
    line += QString::number(this->j);
    line+= " \t";
    if (this->isPositive){
        line += QString::number(1);
    } else {
        line += QString::number(-1);
    }
    line+= " \t";
    line += QString::number(this->energy);
    for (int i=0; i<this->numberWidths; i++){
        line+= " \t";
        line += QString::number(widths[i].getValue());
    }

    if (this->isPrototype){
    line+= " \t";

        if (this->variationEnabled){
            line += "T";
        } else {
            line += "F";
        }

        line+= " \t";
        line += QString::number(this->energyVariation);

        for (int i=0; i<this->numberWidths; i++){
            line+= " \t";
            line += QString::number(widths[i].getVariation());
        }

        line +=" \t";
        line += this->comment;
        }

    return line;
}


QString GecccosPole::getVariationEnabled(){
    if (this->variationEnabled){
        return "T";
    }
    return "F";
}

void GecccosPole::setVariationEnabled(QString newValue){
    if (newValue.toLower().contains("t")){
        this->variationEnabled=true;
    } else {
        this->variationEnabled=false;
    }

}
