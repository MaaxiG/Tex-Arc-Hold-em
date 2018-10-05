#ifndef POKERCLIENT_H
#define POKERCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "include/core/player.h"

class PokerClient : public QObject
{
    Q_OBJECT

public:
    explicit PokerClient();
    Player* p;
    QTcpSocket* socket;
};

#endif // POKERCLIENT_H
