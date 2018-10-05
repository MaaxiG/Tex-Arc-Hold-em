#ifndef POKERTABLE_H
#define POKERTABLE_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <include\network\pokerclient.h>
#include "include/core/gameengine.h"

class MasterNetwork;

class PokerTable : public QObject
{
    Q_OBJECT

public:
    explicit PokerTable(QObject *parent);
    GameEngine* game;
    QString ID;

    QHash<QString, PokerClient*> *clientList;
    bool hasFreePlace();
    void addPlayer(PokerClient* client);
    void leavePlayer(QString token);
    QList<QString>* getTableData();
    QByteArray prepareDataForClient(QString stateNumber, QList<QString>* messages);
    void sendDataToClient(QString stateNumber, QList<QString> *messages, QTcpSocket *client);
    void sendDataToAllClient(QString stateNumber, QList<QString> *messages, QString exceptClientToken = nullptr);
public slots:
    void readyRead();
    void nextPlayer(int playerIndex, int playerBet, int currentBet);
    void nextRound(bool gameEnded, QVector<Card*>* cards);
    void sendCards(QString c1, QString c2, QString token);
    void newGame(int smallBlind, int indexOfSmallBlind, int bigBlind, int indexOfBigBlind);
};

#endif // POKERTABLE_H
