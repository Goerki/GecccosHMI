#include "gecccosstates.h"
GecccosStates::GecccosStates(){

}

GecccosStates::GecccosStates(QString poleStatesFile)
{
    QFile dimensionFile(poleStatesFile);
    if(!dimensionFile.open(QIODevice::ReadOnly)){
        //file not opened correctly
        std::cout << "file not opened correctly";
        exit(0);
    }
    QTextStream* textStream = new QTextStream(&dimensionFile);
    QString line;
    do {
        line = textStream->readLine();
    }while (!line.contains("partitio"));
    QList<QString> keyList = line.split(" ",Qt::SkipEmptyParts);
    setKeyOrder(keyList);


    while(!textStream->atEnd()){
        QString line = textStream->readLine();
        QList<QString> splitLine = line.split(" ",Qt::SkipEmptyParts);
        if (splitLine.size()>2){
            createWidthFromLine(splitLine);
        }
    }
}


void GecccosStates::createWidthFromLine(QList<QString> line){
    GecccosPoleWidth width= GecccosPoleWidth();
    width.apr=line[this->getIndexForKey(Apr)].toInt();
    width.partition=line[getIndexForKey(partitio)].toInt();
    width.Projectile=line[getIndexForKey(Pr)];
    width.aTa =line[getIndexForKey(Ata)].toInt();
    width.target=line[getIndexForKey(Ta)];
    width.jTot=fractionToInt(line[getIndexForKey(Jtotpi)]);
    width.iProjectile=fractionToInt(line[getIndexForKey(Iprpi)]);
    width.iTarget=fractionToInt(line[getIndexForKey(Itapi)]);
    width.iTot=fractionToInt(line[getIndexForKey(I)]);
    width.one=line[getIndexForKey(one)].toInt();
    width.qval=line[getIndexForKey(Qval)].toDouble();
    width.enerDelta=line[getIndexForKey(enerDelta)].toDouble();
    width.hbc2mc2=line[getIndexForKey(hbc2mc2)].toDouble();

    states[width.jTot].append(width);
}

int GecccosStates::fractionToInt(QString fraction){
    int value=fraction.mid(0,1).toInt();
    if (!fraction.contains("/")){
        value=value*2;
    }
    if (fraction.contains("-")){
        value=value*-1;
    }
    return value;
}

void GecccosStates::setKeyOrder(QList<QString> keys){

    for (int i=0; i<keys.size(); i++){
        if (keys[i].contains("partitio")){
            this->keyOrder.insert(partitio, i);
        } else if (keys[i].contains("A_pr")){
            this->keyOrder.insert(Apr, i);
        } else if (keys[i].contains("Pr")){
            this->keyOrder.insert(Pr, i);
        }else if (keys[i].contains("A_ta")){
            this->keyOrder.insert(Ata, i);
        }else if (keys[i].contains("Ta")){
            this->keyOrder.insert(Ta, i);
        }else if (keys[i].contains("Jtot_pi")){
            this->keyOrder.insert(Jtotpi, i);
        }else if (keys[i].contains("I_pr_pi")){
            this->keyOrder.insert(Iprpi, i);
        }else if (keys[i].contains("I_ta_pi")){
            this->keyOrder.insert(Itapi, i);
        }else if (keys[i].contains("I")){
            this->keyOrder.insert(I, i);
        }else if (keys[i].contains("1")){
            this->keyOrder.insert(one, i);
        }else if (keys[i].contains("Q-val")){
            this->keyOrder.insert(Qval, i);
        }else if (keys[i].contains("enerDelta")){
            this->keyOrder.insert(enerDelta, i);
        }else if (keys[i].contains("hbc2mc2")){
            this->keyOrder.insert(hbc2mc2, i);
        }
    }
}

GecccosPoleWidth GecccosStates::getWidthFor(int jTot, bool parity, int n, double value){
    if (!parity && jTot>0){
        jTot*=-1;
    }
    GecccosPoleWidth pole;
    GecccosPoleWidth root = states[jTot][n];
    pole.value = value;
    pole.apr=root.apr;
    pole.aTa=root.aTa;
    pole.description=root.description;
    pole.enerDelta=root.enerDelta;
    pole.hbc2mc2=root.hbc2mc2;
    pole.iProjectile=root.iProjectile;
    pole.iTarget=root.iTarget;
    pole.iTot=root.iTot;
    pole.jTot=root.jTot;
    pole.one=root.one;
    pole.partition=root.partition;
    pole.Projectile=root.Projectile;
    pole.qval=root.qval;
    pole.target=root.target;
    pole.variation=root.variation;

    return pole;

}

int GecccosStates::getIndexForKey(Key key){
    return keyOrder[key];
}
