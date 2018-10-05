#ifndef PROBA_H
#define PROBA_H
#include "QString"
#include "QVector"

class Proba
{
private:
    QString name;
    QVector<float> allProba;
    bool sameColor;
public:
    Proba(QString _name, QVector<float> _allProba, bool same);
    QString getName(){return name;}
    bool isSameColor(){return sameColor;}
    float getProba(int nbPlayer);
};

#endif // PROBA_H
