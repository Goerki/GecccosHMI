#include "gecccoscomment.h"

GecccosComment::GecccosComment(QString line)
{
this->name="comment";
    this->identifyer="comment";
    this->mandatory=true;
    this->line=line;
    this->description="basic comment";
}

void GecccosComment::setValueFromStream(QTextStream* streamPointer) {

    this->line = streamPointer->readLine();
    return;
}

QString GecccosComment::toString(){
    return this->line;
}
