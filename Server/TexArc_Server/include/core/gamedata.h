#ifndef INCLUDEGAMEDATA_H
#define INCLUDEGAMEDATA_H

#include <QDataStream>
#include <QString>
#include "playeraction.h"

class GameData
{
public:
    GameData();
    QString playerToken;
    PlayerAction action;
    quint64 playerBet = 0;
    friend QDataStream &operator<<(QDataStream &inStream, const GameData &data)
    {
        inStream << data.playerToken << data.action << data.playerBet;
        return inStream;
    }

    friend QDataStream &operator>>(QDataStream &inStream, GameData &data)
    {
        inStream >> data.playerToken;

        int playerActionInt;
        inStream >> playerActionInt;
        data.action = static_cast<PlayerAction>(playerActionInt);

        inStream >> data.playerBet;

        return inStream;
    }
};

#endif // INCLUDEGAMEDATA_H
