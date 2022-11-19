#ifndef GECCCOSELEMENT_H
#define GECCCOSELEMENT_H
#include <QObject>
#include <QTextStream>


class GecccosElement {
public:
    enum type {parameter, list, table, map, poles};
    QString virtual toString();
    static GecccosElement::type getTypeFromString(QString string);
    void setValueFromStream(QTextStream* stream);
    QString getName();
    QString getIdentifyer();
    QString getDescription();
protected:
    QString name;
    QString identifyer;
    bool mandatory;
    QString description;

};

#endif // GECCCOSELEMENT_H
