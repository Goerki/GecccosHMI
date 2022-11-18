#ifndef GECCCOSPOLE_H
#define GECCCOSPOLE_H

#include <QObject>
#include "gecccospolewidth.h"
#include "gecccosstates.h"

class GecccosPole
{



public:
    GecccosPole(int numberWidths);
    int numberWidths;
    int j;
    bool isPositive;
    double energy;
    QList<GecccosPoleWidth> widths;
    double getValue(int index);
    QString comment;
    double energyVariation;
    bool variationEnabled;
    GecccosPoleWidth* getWidthOfIndex(int index);
    QString toString();
    QString getComment();
    QString getVariationEnabled();
    QString setVariationEnabled(QString newValue);

};

#endif // GECCCOSPOLE_H
