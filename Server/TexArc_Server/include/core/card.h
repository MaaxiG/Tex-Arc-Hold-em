#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QStringBuilder>
#include <QObject>
#include <QMetaEnum>

///
/// \author Herbelin Ludovic
/// \brief The Card class represents a standard playing card with its rank and its suit
/// the class also has helpers to help display and get the card as id for the OMPEval lib
///
class Card : public QObject
{
    Q_OBJECT

public:
    // Added FirstRank|Suit and LastRank|Suit to iterate over the enum values
    enum Rank {
        Two = 0,
        Three = 1,
        Four = 2,
        Five = 3,
        Six = 4,
        Seven = 5,
        Eight = 6,
        Nine = 7,
        Ten = 8,
        Jack = 9,
        Queen = 10,
        King = 11,
        Ace = 12,

        FirstRank = Two,
        LastRank = Ace
    };
    Q_ENUM(Rank)

    enum Suit
    {
        Spades = 0,
        Hearts = 1,
        Clubs = 2,
        Diamonds = 3,


        FirstSuit = Spades,
        LastSuit = Diamonds
    };
    Q_ENUM(Suit)

    Card(Card::Suit suit, Card::Rank rank);
    // used to parse IDs for the library
    uint getCardID();
    QString getCardName();
    QString getCardFullName();
    QString toString();

    QString cardStr;

    Card::Suit suit;
    Card::Rank rank;
    int value;

private:

};
#endif // CARD_H
