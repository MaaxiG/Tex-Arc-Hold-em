#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <QVector>
#include <QMap>
#include <QObject>

#include "gamedata.h"
#include "deck.h"
#include "gameturn.h"
#include "playeraction.h"
#include "playergame.h"
#include "player.h"
#include "include/core/ai.h"
#include "libs/OMPEval-master/omp/HandEvaluator.h"

///
/// \brief The GameEngine class is the core class of the game. It handles the players actions and the game's flow.
/// \author Herbelin Ludovic
///
class GameEngine : public QObject
{
    Q_OBJECT
private:
    static const int MAX_PLAYERS = 10;

    // functional player and game objects

    Player *dealer = nullptr;
    AI *ai;
    Player *smallBlind = nullptr;
    Player *bigBlind = nullptr;

    QVector<Card *> openCards;
    GameTurn *turn;

    int nSmallBlind = 5;


    Player* currentPlayer;


    // game-related objects
    int nPlayers = 0;
    Deck deck;

    quint64 pot = 0;

    // game-related functions
    void createPlayerGames();
    QVector<PlayerGame *> findWinner();
    void distributeGains(Player *player);
    void distributeGains(QVector<Player*> players);
    bool checkGameState();
    void distributeCards();
    void revealCards(int n);

    // helpers and getters

    Player* getNextPlayer(Player *p);

    Player* setNextPlayer(Player* player);
    QVector<PlayerGame*> getPlayersStillInGame();

public:
    GameEngine();
    ~GameEngine();

    quint64 currentBet = 0;
    PlayerGame *getPlayerGame(Player *player);
    Player* players[MAX_PLAYERS];
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    int indexOfPlayer(Player *p);
    void initGame();

    // debug only
    void dummyGame();

    QVector<PlayerGame*> playerGames;
    Player* getCurrentPlayer();
    int getNbPlayers();


    QString getHandStr(uint16_t handValue);
    uint16_t evaluateHand(PlayerGame *game);
    quint64 getPot();

public slots:
    void onUserAction(PlayerAction action, quint64 bet);
signals:
    void newGame(int smallBlind, int indexOfSmallBlind, int bigBlind, int indexOfBigBlind);
    void nextPlayer(int playerIndex, quint64 playerBet = 0, quint64 currentBet = 0);
    void turnEnded(bool gameEnded, QVector<Card*>* cards);
    void giveCards(QString c1, QString c2, QString playerToken);
};

#endif // GAMEENGINE_H
