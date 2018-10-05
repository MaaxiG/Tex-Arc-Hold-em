#include "include/core/proba.h"
Proba::Proba(QString _name, QVector<float> _allProba, bool _same)
{
    name = _name;
    allProba = _allProba;
    sameColor = _same;
}
float Proba::getProba(int nbPlayer){
    return allProba.at(nbPlayer - 2);
}
