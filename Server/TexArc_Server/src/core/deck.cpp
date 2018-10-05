#include "include/core/deck.h"

Deck::Deck()
{
    resetDeck();
}

Deck::~Deck()
{
    for(Card *card : cards)
        delete card;
}

Card *Deck::draw()
{
    return cards.takeFirst();
}

int myrandom (int i) {
    srand(time(nullptr));
    return rand() % i;
}

///
/// \brief Deck::shuffle the cards in the deck
/// We're not sure about the complexity of the random_shuffle function but since we only shuffle the deck (always 52 elements)
/// once at every start of the game it's probably ok.
/// A game usually lasts around 3 minutes depending on how many players there is
///
void Deck::shuffle()
{
    std::random_shuffle(cards.begin(), cards.end(), myrandom);
}

void Deck::resetDeck()
{
    for(int iSuit = Card::FirstSuit; iSuit <= Card::LastSuit; iSuit++)
    {
        for(int iRank = Card::FirstRank; iRank <= Card::LastRank; iRank++)
        {
            QString str = toString();
            cards.append(new Card(static_cast<Card::Suit>(iSuit),
                                  static_cast<Card::Rank>(iRank)));
        }
    }
    shuffle();
}


QString Deck::toString()
{
    QString str;
    for(Card* card : cards)
    {
        str += card->toString() + "\n";
    }

    return str;
}

