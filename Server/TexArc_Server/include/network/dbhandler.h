#ifndef DBHANDLER_H
#define DBHANDLER_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "include/core/player.h"


///
/// \author Herbelin Ludovic
/// \brief The DBHandler class was meant as a static-like class to handle the databases operations
/// Static classes don't exist in C++ but we achieve it more or less the same way by having static functions only
/// If you want to compile you need to have the libmysql.dll (32 or 64bits depending on your QtCreator) in your compiler folder
class DBHandler
{
    static QSqlDatabase db;
    DBHandler();
public:
    static bool connect();
    static bool updatePlayerMoney(Player *player, quint64 newAmount);
    static Player getPlayer(QString nickname);
    static bool insertPlayer(QString nickname, QString email, QString password);
    static QList<Player> getAllPlayers();

};

#endif // DBHANDLER_H
