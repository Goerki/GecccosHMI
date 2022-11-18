#ifndef GECCCOSSTATES_H
#define GECCCOSSTATES_H

#include <QList>
#include <QMap>
#include "gecccospolewidth.h"
#include <QFile>
#include <iostream>
#include <QTextStream>


class GecccosStates
{
public:
    GecccosStates();
    GecccosStates(QString poleStatesFile);
    GecccosPoleWidth getWidthFor(int jTot, bool parity, int n, double value);
private:
    QMap<int, QList<GecccosPoleWidth>> states;
    enum Key {partitio, Apr, Pr, Ata,Ta,Jta,Tpr, Jtotpi, Iprpi, Itapi, I, one, hbc2mc2, Qval, enerDelta };
    QMap<Key, int> keyOrder;
    int getIndexForKey(Key key);
    void setKeyOrder(QList<QString> keys);
    void createWidthFromLine(QList<QString> line);
    int fractionToInt(QString fraction);

};

#endif // GECCCOSSTATES_H
