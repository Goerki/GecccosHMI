#include "gecccostext.h"

GecccosText::GecccosText()
{
    text= "";

}


void GecccosText::setText(QString newText){
    text = newText;
}

QString GecccosText::toString() override{
    return text;
}

bool GecccosText::isSet(){
    return text=="";
}
