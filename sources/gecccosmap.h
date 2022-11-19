#ifndef GECCCOSMAP_H
#define GECCCOSMAP_H

#include "gecccoselement.h"
#include "gecccosparameter.h"

class GecccosMap : public GecccosElement
{
    QList<GecccosParameter> map;
public:
    GecccosMap(QString name, QString identifyer, QString description, bool mandatory);
    void addParameter(QString name, QString identifyer, QString description, bool mandatory);
    void setValueFromStream(QTextStream* stream);
    QString getName();
    int getSize();
    GecccosParameter* getParam(int index);
    QString toString() override;

};

#endif // GECCCOSMAP_H
