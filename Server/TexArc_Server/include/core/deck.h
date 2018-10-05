#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <ctime>
#include <QVector>

///
/// \author Herbelin Ludovic
/// \brief The Deck class is a container for Card objects. It also has helpers to shuffle the cards and get one from it.
/// \see Card
///
class Deck
{
private:
    QVector<Card*> cards;
public:
    Deck();
    ~Deck();
    Card *draw();
    void shuffle();
    void resetDeck();

    QString toString();
};

#endif // DECK_H
