#ifndef POLEDIMENSIONS_H
#define POLEDIMENSIONS_H

#include <QObject>

class PoleDimensions
{

public:
    PoleDimensions(QString line);
    int getJ();
    int getNumberWidths();
    bool isPositive();

private:
    int j;
    bool parity;
    int numberWidths;


};

#endif // POLEDIMENSIONS_H
