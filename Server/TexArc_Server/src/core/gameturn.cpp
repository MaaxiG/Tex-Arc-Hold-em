#include "include/core/gameturn.h"

GameTurn::GameTurn(Player *startPlayer)
{
    this->startPlayer = startPlayer;
}

bool GameTurn::isStartPlayer(Player *player)
{
    return player == startPlayer;
}
