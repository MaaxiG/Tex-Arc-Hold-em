#include "include\network\pokertable.h"
#include "include/network/masternetwork.h"

PokerTable::PokerTable(QObject *parent)
{
    this->setParent(parent);
    clientList = new QHash<QString, PokerClient*>();
    game = new GameEngine();
    connect(game, &GameEngine::nextPlayer, this, &PokerTable::nextPlayer);
    connect(game, &GameEngine::turnEnded, this, &PokerTable::nextRound);
    connect(game, &GameEngine::giveCards, this, &PokerTable::sendCards);
    connect(game, &GameEngine::newGame, this, &PokerTable::newGame);
}

bool PokerTable::hasFreePlace()
{
    if(game->getNbPlayers() < 10)
        return true;
    else
        return false;
}

void PokerTable::addPlayer(PokerClient *client)
{
    game->addPlayer(client->p);

    clientList->insert(client->p->getToken(), client);
    sendDataToAllClient("3", new QList<QString>{"9", QString::number(game->indexOfPlayer(client->p)),
                                                                     client->p->getNickName(),
                                                                     QString::number(client->p->getMoney())}, client->p->getToken());

    sendDataToClient("4", getTableData(), client->socket);

    if(game->getNbPlayers() == 2)
    {
        game->initGame();
    }
}

void PokerTable::leavePlayer(QString token)
{

    PokerClient *tempClient = clientList->find(token).value();
    sendDataToAllClient("3", new QList<QString>{"4", QString::number(game->indexOfPlayer(tempClient->p))}, token);
    game->removePlayer(tempClient->p);
    tempClient->socket->disconnect();
    connect(tempClient->socket, &QTcpSocket::readyRead, qobject_cast<MasterNetwork*>(this->parent()), &MasterNetwork::handleClientChoice);
    clientList->remove(token);
}

QList<QString> *PokerTable::getTableData()
{
    QList<QString>* data = new QList<QString>();
    data->append(QString::number(game->getPot()));
    data->append(QString::number(game->indexOfPlayer(game->getCurrentPlayer())));

    for(Player* p : game->players)
    {
        if(p == nullptr)
        {
            data->append("-1");
            continue;
        }

        data->append(QString::number(game->indexOfPlayer(p)));
        data->append(p->getNickName());
        data->append(QString::number(p->getMoney()));
        if(game->getPlayerGame(p) == nullptr)
        {
            data->append("0");
            data->append("1");
            continue;
        }
        data->append(QString::number(game->getPlayerGame(p)->bet));
        if(game->getPlayerGame(p)->fold)
            data->append("1");
        else
            data->append("0");

    }

    return data;
}

QByteArray PokerTable::prepareDataForClient(QString stateNumber, QList<QString> *messages)
{
    qint64 size = stateNumber.toUtf8().size();

    for(int i = 0; i < messages->length(); i++)
    {
        size += messages->at(i).toUtf8().size();
    }

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << size << stateNumber;

    for(int i = 0; i < messages->length(); i++)
    {
        //qDebug() << messages->at(i) << "\n";
        out << messages->at(i);
    }

    return block;
}

void PokerTable::readyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(QObject::sender());

    QDataStream in(senderSocket);
    qint32 size = -1;

    // When not enough data has been received, stop
    if (senderSocket->bytesAvailable() < sizeof (qint32))
    {
         return;
    }
    in >> size;

    // When not enough data has been received, stop
    if (senderSocket->bytesAvailable() < size)
    {
         return;
    }

    // Get the useful data
    int state;
    in >> state;

    QString token;
    in >> token;

    if(clientList->find(token) == clientList->end())
        return;

    if(state == 0)
    {

    }

    if(game->getCurrentPlayer()->getToken() != token)
        return;


    switch (state)
    {
        case 1:{
            sendDataToAllClient("3", new QList<QString>{"5", QString::number(game->indexOfPlayer(game->getCurrentPlayer())),
                                                             QString::number(game->currentBet)});
            game->onUserAction(PlayerAction::Call, 0);

            break; //call
        }

        case 2:{
            sendDataToAllClient("3", new QList<QString>{"7", QString::number(game->indexOfPlayer(game->getCurrentPlayer()))});

            game->onUserAction(PlayerAction::Fold, 0);

            break; //fold
        }

        case 3:{
            sendDataToAllClient("3", new QList<QString>{"4", QString::number(game->indexOfPlayer(game->getCurrentPlayer()))});
            game->onUserAction(PlayerAction::Check, 0);

            break; //check
        }

        case 4:{
            QString bet;
            in >> bet;

            sendDataToAllClient("3", new QList<QString>{"6", QString::number(game->indexOfPlayer(game->getCurrentPlayer())), bet});
            game->onUserAction(PlayerAction::Bet, bet.toUInt());

            break; //bet
        }
    }

}

void PokerTable::nextPlayer(int playerIndex, int playerBet, int currentBet)
{
    sendDataToAllClient("3", new QList<QString>{"2", QString::number(playerIndex)});
    sendDataToClient("3", new QList<QString>{"3", QString::number(currentBet), QString::number(playerBet)}, clientList->find(game->players[playerIndex]->getToken()).value()->socket);
}

void PokerTable::nextRound(bool gameEnded, QVector<Card*>* cards)
{
    QString cardString = "";
    for(Card* c : *cards)
    {
        cardString += c->getCardFullName() + ";";
    }
    sendDataToAllClient("3", new QList<QString>{"8", QString::number(game->getPot()), cardString});
}

void PokerTable::sendCards(QString c1, QString c2, QString token)
{
    sendDataToClient("3", new QList<QString>{"1", c1, c2}, clientList->find(token).value()->socket);
}

void PokerTable::newGame(int smallBlind, int indexOfSmallBlind, int bigBlind, int indexOfBigBlind)
{
    sendDataToAllClient("3", new QList<QString>{"0", QString::number(smallBlind), QString::number(indexOfSmallBlind), QString::number(bigBlind), QString::number(indexOfBigBlind)});
}

void PokerTable::sendDataToClient(QString stateNumber, QList<QString> *messages, QTcpSocket *client)
{
    QByteArray data = prepareDataForClient(stateNumber, messages);

    client->write(data);
    client->flush();
}

void PokerTable::sendDataToAllClient(QString stateNumber, QList<QString>* messages, QString exceptClientToken)
{
    QByteArray data = prepareDataForClient(stateNumber, messages);

    for(QHash<QString, PokerClient*>::iterator i = clientList->begin(); i != clientList->end(); i++)
    {
        if(i.key() != exceptClientToken)
        {
            qDebug() << i.key();
            i.value()->socket->write(data);
            i.value()->socket->flush();
        }
    }
}
