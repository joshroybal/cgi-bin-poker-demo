#include "poker.hpp"

std::ostream& operator<<(std::ostream& ostr, const Card& card)
{   
    ostr << "<img src=\"/cards/deck/";
    switch (card.rank_) {
        case two   : ostr << "2";   break;
        case three : ostr << "3";   break;
        case four  : ostr << "4";   break;
        case five  : ostr << "5";   break;
        case six   : ostr << "6";   break;
        case seven : ostr << "7";   break;
        case eight : ostr << "8";   break;
        case nine  : ostr << "9";   break;
        case ten   : ostr << "10";  break;
        case jack  : ostr << "j";   break;
        case queen : ostr << "q";   break;
        case king  : ostr << "k";   break;
        case ace   : ostr << "a";   break;
    }
    switch (card.suit_) {
        case clubs    : ostr << "c";    break;
        case diamonds : ostr << "d";    break;
        case hearts   : ostr << "h";    break;
        case spades   : ostr << "s";    break;
    }        
    ostr << ".jpg\">";
    return ostr;
}

// Hand class methods
void Hand::display()
{
    std::cout << "\n<div>";
    for (int i = 0; i < size; i++) 
        std::cout << cards[i] << ' ';
    std::cout << "</div>";
}

int Hand::isPair()
{
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	return 0;
}

int Hand::isTwoPair()
{
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	return 0;
}

int Hand::isThreeOfKind()
{
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	return 0;
}

int Hand::isStraight()
{
	for (int i = 0; i < size-1; i++)
		if (cards[i+1].rank_ - cards[i].rank_ != 1) return 0;
	if (cards[0].rank_ == two && cards[4].rank_ == ace)
		for (int i = 0; i < size-2; i++)
			if (cards[i+1].rank_ - cards[i].rank_ != 1) return 0;
	return 1;
}

int Hand::isFlush()
{
	for (int i = 1; i < size; i++)
		if (cards[i].suit_ != cards[0].suit_) return 0;
	return 1;
}

int Hand::isFullHouse()
{
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ != cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ != cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	return 0;
}

int Hand::isFourOfKind()
{
	if (cards[0].rank_ == cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ != cards[4].rank_) return 1;
	if (cards[0].rank_ != cards[1].rank_
	    && cards[1].rank_ == cards[2].rank_
	    && cards[2].rank_ == cards[3].rank_
	    && cards[3].rank_ == cards[4].rank_) return 1;
	return 0;
}

int Hand::isStraightFlush()
{
	if (isStraight() && isFlush()) return 1;
	return 0;
}

void Hand::scoreHand()
{
    if (isStraightFlush()) { 
        std::cout << "<div>straight flush</div>";
        return;
    }
    if (isFourOfKind()) {
        std::cout << "<div>four of a kind</div>";
        return;
    }
    if (isFullHouse()) {
        std::cout << "<div>full house</div>";
        return;
    }
    if (isFlush()) { 
        std::cout << "<div>flush</div>";
        return;
    }
    if (isStraight()) { 
        std::cout << "<div>straight</div>";
        return;
    }
    if (isThreeOfKind()) {
        std::cout << "<div>three of a kind</div>";
        return;
    }
    if (isTwoPair()) { 
        std::cout << "<div>two pair</div>";
        return;
    }
    if (isPair()) {
        std::cout << "<div>pair</div>";
        return;
    }
    // if it's a high card hand, six is the lowest possible
    switch (cards[4].rank_) {
        case six   : std::cout << "\n<div>six high</div>";	break;
        case seven : std::cout << "\n<div>seven high</div>";   	break;
        case eight : std::cout << "\n<div>eight high</div>";   	break;
        case nine  : std::cout << "\n<div>nine high</div>";   	break;
        case ten   : std::cout << "\n<div>ten high</div>";  	break;
        case jack  : std::cout << "\n<div>jack high</div>";   	break;
        case queen : std::cout << "\n<div>queen high</div>";   	break;
        case king  : std::cout << "\n<div>king high</div>";   	break;
        case ace   : std::cout << "\n<div>ace high</div>";   	break;
    }    
}

void Hand::sort()
{
	int i, j;
	Rank temprank;
	Suit tempsuit;

	for (i = 1; i < size; i++)	{ // sort {a[0],...,a[i]}:
		temprank = cards[i].rank_;
		tempsuit = cards[i].suit_;
		for (j = i; j > 0 && cards[j-1].rank_ > temprank; j--)	{
			cards[j].rank_ = cards[j-1].rank_;
			cards[j].suit_ = cards[j-1].suit_;
		}
		cards[j].rank_ = temprank;
		cards[j].suit_ = tempsuit;
	}
}

// Deck class methods
Deck::Deck()
{
	for (int i = 0; i < 52; i++) {
		cards[i].rank_ = Rank(i%13);
		cards[i].suit_ = Suit(i/13);
	}
	top = 0;
}

void Deck::deal(Hand& hand, unsigned size)
{
	for (int i = 0; i < size; i++)
		hand.cards[i] = cards[top++];
	hand.sort();
}

void Deck::dealHands(Hand* playerHands, int n)
{
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < 5; j++) 
            playerHands[i].cards[j] = cards[n*j + i];
    for (int i = 0; i < n; i++)
        playerHands[i].sort();
    top += n*5;
}

void Deck::reconstitute(Hand* playerHands, int n)
{
    int m = 52 - top;
    for (int i = 0; i < m; i++)
        cards[i] = cards[top +i];
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < 5; j++) 
            cards[m + 5*i + j] = playerHands[i].cards[j];
    top = 0;
}

void Deck::perfectShuffle()
{
    int n = 52;
    Card tmp[n];

    for (int i = 0; i < n; i += 2) {
        tmp[i] = cards[i/2];
        tmp[i+1] = cards[i/2+n/2];
    }
    for (int i = 0; i < n; i++)
        cards[i] = tmp[i];
}

void Deck::cut()
{
    int n = 52;
    for (int i = 0; i < n/2; i++) {
        Card tmp = cards[i];
        cards[i] = cards[i+n/2];
        cards[i+n/2] = tmp;
    }
}
