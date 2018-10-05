#include "include/network/dbhandler.h"

bool DBHandler::connect()
{
    // In the future these should be in a separated file
    const QString DB_USER = "texarc_client";
    const QString DB_PWD = "";
//    const QString DB_PWD = "Texas8";
    const QString DB_HOST ="157.26.83.20";
    const QString DB_NAME = "texarcholdem";
    const int DB_PORT = 3306;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DB_HOST);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PWD);
    db.setPort(DB_PORT);

    bool ok = db.open();
    return ok;
}

DBHandler::DBHandler()
{
}

bool DBHandler::updatePlayerMoney(Player *player, quint64 newAmount)
{
    const QString queryStr = "UPDATE user SET money = :money WHERE nickname = :nickname";

    QSqlQuery query;
    query.prepare(queryStr);

    query.bindValue(":nickname", player->getNickName());
    query.bindValue(":money",QVariant(QString::number(newAmount)));

    query.exec();
    return query.next();
}

Player DBHandler::getPlayer(QString nickname)
{
    const QString queryStr = "SELECT nickname, money FROM user WHERE nickname = :nickname";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":nickname", nickname);
    query.exec();

    Player p;
    if(query.next())
    {
        p = Player(query.value(0).toString(), query.value(1).toUInt(), "");
    }
    return p;
}

bool DBHandler::insertPlayer(QString nickname, QString email, QString password)
{
    const QString queryStr = "INSERT INTO user(nickname, email, money, password) VALUES(:nickname, :email, :money, :password)";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":nickname", nickname);
    query.bindValue(":email", email);
    query.bindValue(":money", 30000);
    query.bindValue(":password", password);

    query.exec();
    QString lastError = query.lastError().text();
    return query.next();
}

bool checkPassword(QString nickname, QString password)
{
    const QString queryStr = "SELECT password FROM user WHERE nickname = :nickname";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":nickname", nickname);
    query.exec();

    if(query.next())
    {
        if(QString::compare(query.value(0).toString(),password) == 0)
            return true;
    }

    return false;
}

QList<Player> DBHandler::getAllPlayers()
{
    const QString queryStr = "SELECT nickname, money FROM user";

    QSqlQuery query;
    query.prepare(queryStr);

    QList<Player> players;

    while(query.next())
    {
       players.append(Player(query.value(0).toString(), query.value(1).toUInt(), ""));
    }

    return players;
}


