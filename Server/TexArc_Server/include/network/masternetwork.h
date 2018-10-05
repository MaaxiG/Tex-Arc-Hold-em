#ifndef MASTERNETWORK_H
#define MASTERNETWORK_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <include\network\pokerclient.h>
#include <include\network\pokertable.h>
#include <include/network/dbhandler.h>

class MasterNetwork : public QObject
{
    Q_OBJECT
public:
    explicit MasterNetwork(QObject *parent = nullptr);

private:

    QTcpServer *connectServer;
    QHash<QString, PokerClient*> *clientList;
    QVector<PokerTable*> *tableList;
    PokerTable* getNextOpenTable();
    PokerClient* connectPlayer(QString nickname, QString token, QTcpSocket *clientSocket);
    PokerClient* getPlayerInfos(QString nickname);
    PokerClient* signInPlayer(QString nickname, QString passHash, QString mail);
    void sendDataToClient(QString stateNumber, QList<QString>* messages, QTcpSocket* client);
    bool checkAlreadyConnected(QString token);

signals:

public slots:
    void handleNewConnection();
    void handleClientChoice();
};

#endif // MASTERNETWORK_H
