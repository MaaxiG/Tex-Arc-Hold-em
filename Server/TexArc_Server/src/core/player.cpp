#include "include/core/player.h"

QString Player::getNickName() const
{
    return nickName;
}

void Player::setNickName(const QString &value)
{
    nickName = value;
}

quint64 Player::getMoney() const
{
    return money;
}

void Player::setMoney(const quint64 &value)
{
    money = value;
}

QString Player::getToken() const
{
    return token;
}

void Player::setToken(const QString &value)
{
    token = value;
}

Player::Player()
{

}
Player::Player(QString nickName, quint64 money, QString token)
{
    setNickName(nickName);
    setMoney(money);
    setToken(token);
}
