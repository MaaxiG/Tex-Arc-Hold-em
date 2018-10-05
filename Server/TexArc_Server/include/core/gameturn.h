#ifndef INCLUDEGAMETURN_H
#define INCLUDEGAMETURN_H

#include "player.h"

///
/// \brief The GameTurn class is a container to help the engine determine when to end the round
/// \author Herbelin Ludovic
/// IE when a player raises we need to make every player follow or fold until we get to the raiser
///
class GameTurn
{
private:
    Player *startPlayer;
public:
    GameTurn(Player *startPlayer);

    bool isStartPlayer(Player *player);
};

#endif // INCLUDEGAMETURN_H
