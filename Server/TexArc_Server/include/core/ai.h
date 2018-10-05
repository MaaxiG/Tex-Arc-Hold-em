#ifndef AI_H
#define AI_H

#include "stats.h"
#include "card.h"
#include "playeraction.h"
#include "player.h"
#include "playergame.h"
#include "time.h"
#include "libs/OMPEval-master/omp/HandEvaluator.h"
#include <QObject>

class AI:public QObject, public Player
{
    Q_OBJECT
public:
    AI(quint64 money);
    QString play();
    QString playPreFlop();
    QString playAfterTurn();
    QString playAfterRiver();
    bool shouldI(int chance);
    int randomRaise(int min, int max);

    void setInfos(PlayerGame *playerGame, int bigBlind, int miseAct, const QVector<Card *> &cards, int nbPlayers){
        openCards = cards;
        this->playerGame = playerGame;
        this->bigBlind = bigBlind;
        this->mise = miseAct;
        this->nbPlayers = nbPlayers;
        if (playerGame->cards.at(0)->suit == playerGame->cards.at(0)->suit)
            sameColor = true;
        else
            sameColor = false;
    }

    QString playAfterFlop();
private:
    QVector<Card *> openCards;
    PlayerGame *playerGame;
    int nbPlayers;
    int bigBlind;
    int mise;
    int maMise = 0;
    bool sameColor;
    Stats *st;
signals:
    void AIPlay(PlayerAction playerAction, quint64 bet);
};

#endif // AI_H
