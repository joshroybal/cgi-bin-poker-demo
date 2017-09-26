#ifndef _DECK_HPP__
#define _DECK_HPP__

#include <iostream>

enum Rank {two, three, four, five, six, seven, eight,
       nine, ten, jack, queen, king, ace};
enum Suit {clubs, diamonds, hearts, spades};

class Card {
    friend class Hand;
    friend class Deck;
    friend std::ostream& operator<<(std::ostream&, const Card&);
public:
    char rank() { return rank_; }
    char suit() { return suit_; }
private:
    Card() { };
    Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) { };
    Card(const Card& c) : rank_(c.rank_), suit_(c.suit_) { };
    ~Card() { };
    Rank rank_;
    Suit suit_;
};

class Hand {
    friend class Deck;
public:
    Hand(unsigned n=5) : size(n) { cards = new Card[n]; }
    ~Hand() { delete [] cards; }
    void display();
    int isPair();
    int isTwoPair();
    int isThreeOfKind();
    int isStraight();
    int isFlush();
    int isFullHouse();
    int isFourOfKind();
    int isStraightFlush();
    void scoreHand();
private:
    unsigned size;
    Card *cards;
    void sort();
};

class Deck {
public:
    Deck();
    void perfectShuffle();
    void cut();
    void deal(Hand&, unsigned =5);
    void dealHands(Hand*, int);
    void reconstitute(Hand*, int);
private:
    unsigned top;
    Card cards[52];
};

#endif
