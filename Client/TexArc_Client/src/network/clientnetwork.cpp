#include "include/network/clientnetwork.h"



ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    //socket->connectToHost("127.0.0.1", quint16(65535));
    connect(socket, &QTcpSocket::readyRead, this, &ClientNetwork::readyRead);
}

void ClientNetwork::networkQuit()
{


}

void ClientNetwork::sendDataToServer(QString stateNumber, QList<QString> *messages)
{
    /**** DATAGRAMS RECEIVED ********************************************/
    /* SignIn               : |size|0|email|nickname|hashedpassword|    */
    /* LogIn                : |size|1|nickname|hashedpassword|          */
    /* SearchTable          : |size|2|hash|                             */
    /* GetPlayerInfo        : |size|3|hash|                             */
    /*************************************************/
    //Sign in : sendDataToServer("0", new QList<QString>{email, nickname, hashedpassword});
    //Log in : sendDataToServer("1", new QList<QString>{nickname, hashedpassword});
    //searchtable : sendDataToServer("2", new QList<QString>{token});
    //Sign in : sendDataToServer("3", new QList<QString>{token});
    qint32 size = stateNumber.toUtf8().size();

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

    socket->write(block);

}

void ClientNetwork::debugSendMessage()
{
    sendDataToServer("0", new QList<QString>{"qq", "qq", "qq"});
}

void ClientNetwork::readyRead()
{
    QDataStream in(socket);
    qint32 size = 0;

    qDebug() << "Message received----------";

    // When not enough data has been received, stop
    if (socket->bytesAvailable() < sizeof (qint32))
    {
         return;
    }
    in >> size;
    qDebug() << "Size : " << size;

    // When not enough data has been received, stop
    if (socket->bytesAvailable() < size)
    {
         return;
    }

    // Get the useful data
    QString state;
    in >> state;

    qDebug() << "State : " << state;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    /**** DATAGRAMS SENT ************************************************/
    /* SignIn success       : send login datagram                       */
    /* Errors               : |size|-1|error message|                   */
    /* LogIn success        : |size|0|hash|+PlayerInfo                  */
    /* SearchTable success  : |size|1|tableID                           */
    /* PlayerInfo           : |size|2|nickname|gold                     */
    /*****************************************/

    qDebug() << "Before switch";

    switch (state.toInt())
    {
        case -1:{
            QString error;
            in >> error;

            qDebug() << error;
            break;
        }

    case 0:{
        qDebug() << "In target";
        QString token, nickname, gold;
        in >> token;
        in >> nickname;
        in >> gold;

        qDebug() << token << " " << nickname << " " << gold;
        break;
    }

    case 1:{
        QString tableID;
        in >> tableID;

        break;
    }

    case 2:{
        QString nickname, gold;
        in >> nickname;
        in >> gold;

    }

    default: qDebug() << "default"; break;

    }
}


