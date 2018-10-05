#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

class Player
{
private:
    QString token;
    QString nickName;
    quint64 money;
public:
    Player();
    Player(QString nickName, quint64 money, QString token);
    QString getNickName() const;
    void setNickName(const QString &value);
    quint64 getMoney() const;
    void setMoney(const quint64 &value);
    QString getToken() const;
    void setToken(const QString &value);
};

#endif // PLAYER_H
