#ifndef GECCCOSPARAMETER_H
#define GECCCOSPARAMETER_H

#include "gecccoselement.h"

class GecccosParameter : public GecccosElement
{
private:
    QString value;
public:
    GecccosParameter(QString name, QString identifyer, QString description, bool mandatory);
    void setValueFromStream(QTextStream* stream);
    void setValueFromStringList(QStringList stringList);
    QString getValue();
    void setValue(QString text);
    QString toString() override;

};

#endif // GECCCOSPARAMETER_H
