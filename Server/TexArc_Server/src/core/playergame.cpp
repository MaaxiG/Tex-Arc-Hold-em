#include "include/core/playergame.h"

void PlayerGame::clear()
{
    bet = 0;
    fold = false;
    cards.clear();
}

void PlayerGame::setCards(const QVector<Card *> &cards)
{
    for(Card *card : cards)
        this->cards.append(card);
}

PlayerGame::PlayerGame(Player *player)
{
    this->player = player;
}
