#include "include/core/card.h"
//COUCOU
Card::Card(Card::Suit suit, Card::Rank rank)
{
    this->suit = suit;
    this->rank = rank;

    cardStr = toString();
}

uint Card::getCardID()
{
    return 4 * rank + suit;
}



QString Card::getCardName(){
    int c = rank+2;
    switch (c) {
    case 10:
        return "T";
        break;
    case 11:
        return "J";
        break;
    case 12:
        return "Q";
        break;
    case 13:
        return "K";
        break;
    case 14:
        return "A";
        break;
    default:
        return QString::number(c);
        break;
    }
}

QString Card::getCardFullName()
{
    QMetaEnum suitMetaEnum = QMetaEnum::fromType<Card::Suit>();
    QString cardName = getCardName();
    if (cardName == "T")
        cardName = "10";
    return getCardName() + QString(suitMetaEnum.valueToKey(this->suit)).at(0).toUpper();
}

QString Card::toString()
{
    QMetaEnum rankMetaEnum = QMetaEnum::fromType<Card::Rank>();
    QMetaEnum suitMetaEnum = QMetaEnum::fromType<Card::Suit>();

    QString str;
    str = rankMetaEnum.valueToKey(this->rank);
    str += " of ";
    str += suitMetaEnum.valueToKey(this->suit);
    return str;
}
