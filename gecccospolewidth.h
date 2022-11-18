#ifndef GECCCOSPOLEWIDTH_H
#define GECCCOSPOLEWIDTH_H
#include <QString>

class GecccosPoleWidth
{
public:
    GecccosPoleWidth();
    double getValue();
    double getVariation();
    int getPartition();
    int getApr();
    int getATa();
    QString getProjectile();
    QString getTarget();
    QString getJTot();
    QString getIProjectile();
    QString getITarget();
    QString getITot();
    int getOne();
    double getHbc2mc2();
    double getQval();
    double getEnerDelta();
    QString getDescription();

    double value;
    double variation;
    int partition;
    int apr;
    int aTa;
    QString Projectile;
    QString target;
    int jTot;
    int iProjectile;
    int iTarget;
    int iTot;
    int one;
    double hbc2mc2;
    double qval;
    double enerDelta;
    QString description;
    QString toString();

};

#endif // GECCCOSPOLEWIDTH_H
