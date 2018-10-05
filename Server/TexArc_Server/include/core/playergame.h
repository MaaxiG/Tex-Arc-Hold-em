#ifndef INCLUDEPLAYERGAME_H
#define INCLUDEPLAYERGAME_H

#include <QVector>
#include "player.h"
#include "card.h"

class PlayerGame
{
public:
    QVector<Card*> cards;
    Player *player;
    bool fold = false;
    quint64 bet;
    void clear();
    void setCards(const QVector<Card *> &cards);
    PlayerGame(Player *player);
};

#endif // INCLUDEPLAYERGAME_H
