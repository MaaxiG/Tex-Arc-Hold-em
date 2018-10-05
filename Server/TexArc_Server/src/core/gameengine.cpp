#include "include/core/gameengine.h"



GameEngine::GameEngine()
{
    std::fill(std::begin(players), std::begin(players) + MAX_PLAYERS, nullptr);
//    ai = new AI(30000);
//    addPlayer(ai);
//    connect(this->ai, &AI::AIPlay, this, &GameEngine::onUserAction);
}

GameEngine::~GameEngine()
{
    for(PlayerGame *pg : playerGames)
    {
        if(pg != nullptr)
        {
            delete pg;
        }
    }

    for(Player *p : players)
        delete p;
}

///
/// \brief GameEngine::getHandStr returns a string to display from the hand "score"
/// \param handValue the hand value from the OMPEval library
/// \return a string to display the type of hand to the player
///
QString GameEngine::getHandStr(uint16_t handValue)
{
    // the library uses ranges for the hand values so we "floor" our value to get the
    // hand type (from the OMPEval doc)
    switch((handValue / omp::HAND_CATEGORY_OFFSET) * omp::HAND_CATEGORY_OFFSET)
    {
        case omp::HIGH_CARD: return "High card";
        case omp::PAIR: return "Pair";
        case omp::TWO_PAIR: return "Two pairs";
        case omp::THREE_OF_A_KIND: return "Three of a kind";
        case omp::STRAIGHT: return "Straight";
        case omp::FLUSH: return "Flush";
        case omp::FULL_HOUSE: return "Full house";
        case omp::FOUR_OF_A_KIND: return "Four of a kind";
        case omp::STRAIGHT_FLUSH: return "Straight flush";
        default: return "incorrect hand value";
    }
}

///
/// \brief GameEngine::evaluateHand is a helper to evaluate a player's hand
/// \param game the PlayerGame object containing the player's hand
/// \return a hand score evaluated by the OMPEval library
///
uint16_t GameEngine::evaluateHand(PlayerGame *game)
{
    omp::Hand hand = omp::Hand::empty();
    omp::HandEvaluator evaluator;
    for(Card *card : game->cards)
        hand += card->getCardID();
    for(Card *card : openCards)
        hand += card->getCardID();
    return evaluator.evaluate(hand);
}

quint64 GameEngine::getPot()
{
    return this->pot;
}


///
/// \brief GameEngine::initGame should be called when starting a new game of poker
///  it creates the PlayerGame objects for each player connected as the game starts
///  and sets the different virtual poker "buttons" (dealer, blinds)
///
void GameEngine::initGame()
{
    createPlayerGames();

    // The virtual poker "buttons"
    dealer = getNextPlayer(currentPlayer);
    smallBlind = getNextPlayer(dealer);
    bigBlind = getNextPlayer(smallBlind);

    currentPlayer = getNextPlayer(bigBlind);

    turn = new GameTurn(currentPlayer);


    for(Player *p : players)
    {
        if(p != nullptr)
            playerGames.append(new PlayerGame(p));
    }
    emit newGame(nSmallBlind, indexOfPlayer(smallBlind), 2*nSmallBlind, indexOfPlayer(bigBlind));
    distributeCards();
}

void GameEngine::createPlayerGames()
{
    // Remove previous player games
    for(PlayerGame *pg : playerGames)
    {
        if(pg != nullptr)
        delete pg;
    }
    playerGames.clear();

    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i] != nullptr)
            playerGames.append(new PlayerGame(players[i]));
    }
}

///
/// \brief GameEngine::findWinner this functions determines which player(s) has the best hand
/// \return a list of PlayerGame of the winner(s). Can have multiple players in case of perfect equality
///
QVector<PlayerGame*> GameEngine::findWinner()
{
    QVector<PlayerGame*> playersLeft = getPlayersStillInGame();


    QVector<PlayerGame *> winners;
    uint16_t winningHand = 0;

    // Evaluate each player's hand
    // If there is a better hand than the current winner's, the evaluated player becomes the winner and the best hand is set to his
    for(PlayerGame *pg : playersLeft)
    {
        uint16_t handValue  = evaluateHand(pg);
        if(handValue > winningHand)
        {
            winners.clear();
            winners.append(pg);
            winningHand = handValue;
        }
        else if(handValue == winningHand)
            winners.append(pg);
    }

    return winners;
}

void GameEngine::distributeGains(Player *player)
{
    QVector<Player*> playerContainer;
    playerContainer.append(player);
    distributeGains(playerContainer);
}

void GameEngine::distributeGains(QVector<Player *> players)
{
    for(Player *player : players)
    {
        player->setMoney(player->getMoney() + pot / players.size());
    }
}

///
/// \brief GameEngine::checkGameState this checks how the game currently is.
/// We need to start a new "round" if all players have checked or call. The game can be ended if there's only 1 player left or it was the last round.
/// \return true if the game is over
///
bool GameEngine::checkGameState()
{
    bool ended = false;
    QVector<PlayerGame *> playersLeft = getPlayersStillInGame();
    if(playersLeft.size() == 1)
    {
        distributeGains(playersLeft.first()->player);
        ended = true;
    }
    else if(turn->isStartPlayer(currentPlayer))
    {
        switch(openCards.size())
        {
            case 0: revealCards(3);break;
            case 3:
            case 4: revealCards(1);break;
            case 5:
                findWinner();
                ended = true;
            break;
        }

        emit turnEnded(ended, &openCards);
    }

    return ended;
}

void GameEngine::distributeCards()
{
    for(PlayerGame* pg : playerGames)
    {
        QVector<Card*> cards;
        cards.append(deck.draw());
        cards.append(deck.draw());
        pg->setCards(cards);

        emit giveCards(pg->cards.first()->getCardFullName(), pg->cards.at(1)->getCardFullName(), pg->player->getToken());
    }
}

void GameEngine::revealCards(int n)
{
    for(int i = 0; i < n; i++)
    {
        this->openCards.append(deck.draw());
    }
}

int GameEngine::indexOfPlayer(Player *p)
{
    if(p == nullptr)
        return -1;
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i] == p)
            return i;
    }
    return -1;
}

void GameEngine::addPlayer(Player *p)
{
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i] == nullptr)
        {
            players[i] = p;
            nPlayers++;
            break;
        }


    }
}

void GameEngine::removePlayer(Player *player)
{
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i] == player)
        {
            getPlayerGame(player)->fold = true;
            nPlayers--;
            players[i] = nullptr;
        }
    }
}

///
/// \brief GameEngine::onUserAction this slots handles the user action as received on the network
/// \param action what does the player do (check, bet, call)
/// \param bet if the player raises, how high is the bet
///
void GameEngine::onUserAction(PlayerAction action, quint64 bet = 0)
{
    PlayerGame *currentPlayerGame = getPlayerGame(currentPlayer);
    switch(action)
    {
        case Call:
            pot += currentBet;
            currentPlayerGame->bet = currentBet;
        break;

        case Bet:
        if(bet > currentBet)
        {
            currentBet = bet;
            pot += currentBet;
            turn = new GameTurn(currentPlayer);
        }
        break;

        case Check:
        break;

        case Fold:
            currentPlayerGame->fold = true;
        break;

    }
    if(!checkGameState())
        setNextPlayer(currentPlayer);
    else
    {
        for(PlayerGame *pg : playerGames)
        {
            if(pg != nullptr)
            {
                delete pg;
            }
        }
        initGame();
    }

    emit nextPlayer(indexOfPlayer(currentPlayer), currentBet, getPlayerGame(currentPlayer)->bet);
}

Player* GameEngine::getNextPlayer(Player *previous)
{
    int previousPlayerIndex = -1;

    if(previous == nullptr)
    {
        previousPlayerIndex = 0;
        return players[previousPlayerIndex];
    }
    else
    {
        for(int i = 0; i < MAX_PLAYERS; i++)
        {
            if(previous == players[i])
            {
                previousPlayerIndex = i;
                break;
            }
        }
    }

    if(previousPlayerIndex == -1)
        return nullptr;

    else
    {
        Player *nextPlayer = players[(previousPlayerIndex + 1) % MAX_PLAYERS];
        if(nextPlayer == nullptr || getPlayerGame(nextPlayer)->fold)
            return getNextPlayer(nextPlayer);
        else
            return nextPlayer;
    }
}

///
/// \brief GameEngine::setNextPlayer this function sets who is the next to play. if it's the ai we make it play automatically.
/// \param player the player that played before
/// \return who is the current player that was setted
///
Player *GameEngine::setNextPlayer(Player *player)
{
    this->currentPlayer = getNextPlayer(player);
    if(currentPlayer == ai)
    {
        ai->play();
        setNextPlayer(currentPlayer);
    }
    return currentPlayer;
}

PlayerGame *GameEngine::getPlayerGame(Player *player)
{
    for(PlayerGame *pg : playerGames)
        if(pg->player == player)
            return pg;
    return nullptr;
}

QVector<PlayerGame *> GameEngine::getPlayersStillInGame()
{
    QVector<PlayerGame*> playersLeft;
    for(PlayerGame *pg : playerGames)
    {
        if(!(pg->fold))
            playersLeft.append(pg);
    }

    return playersLeft;
}

/// for debug purposess
/// \brief GameEngine::dummyGame
///
void GameEngine::dummyGame()
{
    this->ai = new AI(50000);
    Player *max = new Player("Moksam", 50000, "asdqlkwjeqlkwjeqlwkjeqlwkejqwlkje");
    Player *alain = new Player("Alain", 30000, "alkjsdlkasjdlkqjew");
    Player *ludo = new Player("Ludo", 40000, "kajsdlkj");
    Player *celien = new Player("Célien", 35000, "jkasdlkj");
    Player *farrid = new Player("Farrid", 25000, "asjldjasldj");


    addPlayer(ai);
    addPlayer(max);
    addPlayer(alain);
    addPlayer(ludo);
    addPlayer(celien);
    addPlayer(farrid);

    initGame();
    distributeCards();
}


Player *GameEngine::getCurrentPlayer()
{
    return currentPlayer;
}

int GameEngine::getNbPlayers()
{
    return nPlayers;
}
