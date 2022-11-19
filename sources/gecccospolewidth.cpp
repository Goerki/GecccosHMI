#include "gecccospolewidth.h"

GecccosPoleWidth::GecccosPoleWidth()
{
variation=0.0;
}


double GecccosPoleWidth::getValue(){
    return value;
}
double GecccosPoleWidth::getVariation(){
    return variation;
}
int GecccosPoleWidth::getPartition(){
    return partition;
}
int GecccosPoleWidth::getApr(){
    return apr;
}
int GecccosPoleWidth::getATa(){
    return aTa;
}
QString GecccosPoleWidth::getProjectile(){
    return Projectile;
}
QString GecccosPoleWidth::getTarget(){
    return target;
}
QString GecccosPoleWidth::getJTot(){
    QString res;
    if (jTot >0){
        res+="+";
    }
    res+= QString::number(jTot);
    res +="/2";

    return res;
}
QString GecccosPoleWidth::getIProjectile(){
    QString res= "";
    if (iProjectile >0){
        res+="+";
    }
    res+=QString::number(iProjectile);
    res +="/2";
    return res;
}
QString GecccosPoleWidth::getITarget(){
    QString res;
    if (iTarget >0){
        res+="+";
    }
    res+= QString::number(iTarget);
    res +="/2";

    return res;
}
QString GecccosPoleWidth::getITot(){
    QString res;
    if (iTot >0){
        res+="+";
    }
    res+= QString::number(iTot);
    res +="/2";

    return res;
}
int GecccosPoleWidth::getOne(){
    return one;
}
double GecccosPoleWidth::getHbc2mc2(){
    return hbc2mc2;
}
double GecccosPoleWidth::getQval(){
    return qval;
}
double GecccosPoleWidth::getEnerDelta(){
    return enerDelta;
}
QString GecccosPoleWidth::getDescription(){
    return description;
}
