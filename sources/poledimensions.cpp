#include "poledimensions.h"

PoleDimensions::PoleDimensions(QString line)
{
    QStringList list = line.split(" ",Qt::SkipEmptyParts);
    this->parity=list[0].contains("+");
    this->j = list[0].split("/",Qt::SkipEmptyParts)[0].toInt();
    this->numberWidths=list[1].toInt();
}

int PoleDimensions::getJ(){
    return j;
}

int PoleDimensions::getNumberWidths(){
return numberWidths;
}

bool PoleDimensions::isPositive(){
    return parity;
}

