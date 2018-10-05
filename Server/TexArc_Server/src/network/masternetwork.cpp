#include "include\network\masternetwork.h"

MasterNetwork::MasterNetwork(QObject *parent) : QObject(parent)
{
    connectServer = new QTcpServer();
    clientList = new QHash<QString, PokerClient*>();
    tableList = new QVector<PokerTable*>();

    connect(connectServer, &QTcpServer::newConnection, this, &MasterNetwork::handleNewConnection);

    if(connectServer->listen(QHostAddress::Any, quint16(65535)))
    {
        qDebug() << "Server online";
        DBHandler::connect();
    }
    else
    {
        qDebug() << "Server failed";
    }
}

PokerTable *MasterNetwork::getNextOpenTable()
{
    int freeAt = -1;
    for(int i = 0; i < tableList->length(); i++)
    {
        if(tableList->at(i)->hasFreePlace())
        {
            freeAt = i;
            i = tableList->length();
        }
    }

    if(freeAt == -1)
    {
        PokerTable *newPokerTable = new PokerTable(this);
        tableList->append(newPokerTable);
        return newPokerTable;
    }
    else
        return tableList->at(freeAt);
}

PokerClient* MasterNetwork::connectPlayer(QString nickname, QString pass, QTcpSocket* clientSocket)
{
    if(true) //If the player is registered
    {
        if(!checkAlreadyConnected(nickname))
        {
            PokerClient* client = getPlayerInfos(nickname);
            if(client->p->getNickName() == "")
                return nullptr;
            client->socket = clientSocket;
            clientList->insert(client->p->getToken(), client);
            return client;
        }

    }
    return nullptr;
}

PokerClient *MasterNetwork::getPlayerInfos(QString nickname)
{
    //Get player info in the db
    Player p = DBHandler::getPlayer(nickname);
    PokerClient* clientInfo = new PokerClient();
    clientInfo->p = new Player(p.getNickName(), p.getMoney(), p.getNickName());
    return clientInfo;
}

PokerClient* MasterNetwork::signInPlayer(QString nickname, QString passHash, QString mail)
{
    //Ask for db connection
    DBHandler::insertPlayer(nickname, mail, passHash);

    if(true) //If player is not already registered
    {
        return getPlayerInfos(nickname);
    }

    return nullptr;
}

void MasterNetwork::sendDataToClient(QString stateNumber, QList<QString> *messages, QTcpSocket *client)
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
        out << messages->at(i);
    }

    client->write(block);
    client->flush();
}

bool MasterNetwork::checkAlreadyConnected(QString token)
{
    if(clientList->find(token) == clientList->constEnd())
    {
        return false;
    }

    return false;
}

void MasterNetwork::handleNewConnection()
{
    qDebug() << "in";
    QTcpSocket *clientConnection = connectServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::readyRead, this, &MasterNetwork::handleClientChoice);
    qDebug() << "sent message";
}

void MasterNetwork::handleClientChoice()
{
    /********************************************************************/
    /**** DATAGRAMS RECEIVED ********************************************/
    /* SignIn               : |size|0|email|nickname|hashedpassword|    */
    /* LogIn                : |size|1|nickname|hashedpassword|          */
    /* SearchTable          : |size|2|hash|                             */
    /* GetPlayerInfo        : |size|3|hash|                             */
    /********************************************************************/
    /**** DATAGRAMS SENT ************************************************/
    /* SignIn success       : send login datagram                       */
    /* Errors               : |size|-1|error message|                   */
    /* LogIn success        : |size|0|hash|+PlayerInfo                  */
    /* SearchTable success  : |size|1|tableID                           */
    /* PlayerInfo           : |size|2|nickname|gold                     */
    /********************************************************************/

    qDebug() << "Received message-------------";

    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(QObject::sender());

    QDataStream in(senderSocket);
    qint32 size = -1;

    // When not enough data has been received, stop
    if (senderSocket->bytesAvailable() < sizeof (qint32))
    {
         return;
    }

    in >> size;
    qDebug() << "Size : " << size;



    // When not enough data has been received, stop
    if (senderSocket->bytesAvailable() < size)
    {
         return;
    }

    // Get the useful data
    QString state;
    in >> state;

    qDebug() << "before switch";
    qDebug() << "State : " << state;

    switch (state.toInt())
    {
        //Sign in
        case 0:{
            QString mail, nickname, pass;
            in >> mail;
            in >> nickname;
            in >> pass;

            qDebug() << "mail : " << mail;
            qDebug() << "nickname : " << nickname;
            qDebug() << "pass : " << pass;

            PokerClient* acceptSignIn = signInPlayer(nickname, pass, mail);

            if(acceptSignIn != nullptr)
            {
                qDebug() << "Sign in correct";
                //acceptSignIn = connectPlayer(nickname, acceptSignIn->p->getToken(), senderSocket);

                sendDataToClient("0", new QList<QString>{acceptSignIn->p->getToken()}, senderSocket);
                //sendDataToClient("0", new QList<QString>{}, senderSocket);
            }
            else
            {
                sendDataToClient("-1", new QList<QString>{"An error has occured !"}, senderSocket);
            }
            break;
        }

        //log in
        case 1:{
            QString nickname, pass;
            in >> nickname;
            in >> pass;

            PokerClient* acceptConnect = connectPlayer(nickname, pass, senderSocket);
            if(acceptConnect != nullptr)
            {
                sendDataToClient("0", new QList<QString>{acceptConnect->p->getToken()}, senderSocket);
            }
            else
            {
                sendDataToClient("-1", new QList<QString>{"An error has occured !"}, senderSocket);
            }
            break;
        }

        //search table
        case 2:{
            QString hash;
            in >> hash;

            if(hash == "") // if error
            {
                sendDataToClient("-1", new QList<QString>{"An error has occured !"}, senderSocket);
            }
            else
            {
                PokerTable *table = getNextOpenTable();
                senderSocket->disconnect();
                connect(senderSocket, &QTcpSocket::readyRead, table, &PokerTable::readyRead);

                sendDataToClient("1", new QList<QString>{}, senderSocket);

                table->addPlayer(clientList->find(hash).value());



            }

            break;
        }

        //player infos
        case 3:{
            QString token;
            in >> token;

            if(checkAlreadyConnected(token))
            {
                PokerClient* infoClient = getPlayerInfos("qq");

                sendDataToClient("2", new QList<QString>{infoClient->p->getNickName(), infoClient->p->getToken()}, senderSocket);
            }

            break;
        }

        //leaving
        case 4:{

//        QString token;
//            in >> token;

//            if(checkAlreadyConnected(token))
//            {
//                clientList->remove(token);
//            }
            break;
        }

        default: return;

    }
}



