#ifndef STATS_H
#define STATS_H
#include "QVector"
#include "proba.h"
#include "QString"

class Stats
{
private:
    QVector<Proba*> preflopStats;
public:
    Stats();
    int getProbaPreflop(QString card, bool sameColor, int nbPlayer);

};

#endif // STATS_H
