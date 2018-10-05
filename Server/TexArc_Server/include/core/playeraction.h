#ifndef PLAYERACTION_H
#define PLAYERACTION_H

///
/// \author Herbelin Ludovic
/// \brief The PlayerAction enum represents which actions a player can do. Depending on the state of the game, some actions might not be available.
///
enum PlayerAction {
    Call = 1,
    Bet = 2,
    Check = 3,
    Fold = 4
};
#endif // PLAYERACTION_H
