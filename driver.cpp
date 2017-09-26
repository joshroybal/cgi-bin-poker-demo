#include <fstream>
#include <sstream>
#include <cstdlib>
#include "poker.hpp"

const int MAX_BYTES = 80;

void parseData(char *, unsigned&, unsigned&);

int main()
{
    unsigned players, hands;
    float t1, t2, t3, t4;
    char data[MAX_BYTES];

    int length = atoi(getenv("CONTENT_LENGTH"));
    if (length >= MAX_BYTES) return 1;	// that takes care of that
    std::cout << "Content-Type:text/html;charset=iso-8859-1\n\n";
    fread(data, length, 1, stdin);
    

    // extract no. pf players and no. of hands from post data
    parseData(data, players, hands);

    // error checking
    if (players < 2 || players > 10) {
        std::cerr << "\ninvalid no. of players - must be between 2 and 10\n";
        return 1;
    }
    if (hands < 1 || hands > 10) {
        std::cerr << "\ninvalid no. of hands - must be between 1 and 10\n";
        return 1;
    }
    
    Deck* theDeck = new Deck;
    Hand* playerHands = 0;
    playerHands = new Hand[players];
    std::cout << "<!DOCTYPE HTML>";
    std::cout << "\n<html>";
    std::cout << "\n<head>";
    std::cout << "\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    std::cout << "\n<link rel=\"stylesheet\" media=\"all\"  href=\"/includes/style.css\">";
    std::cout << "\n<title>CGI C++ Poker</title>";
    std::cout << "\n</head>";
    std::cout << "\n<body>";
    std::cout << "\n<header><p>CGI C++ POKER</p></header>";
    std::cout << "\n<div><a href=\"/index.php\">Home</a> | <a href=\"/cgipoker.html\">C++ Poker</a></div>";
    for (int i = 0; i < hands; i++) {
        theDeck->cut();
        theDeck->perfectShuffle();
        theDeck->dealHands(playerHands, players);
        std::cout << "\n<p>hand no. " << i+1 << "</p>";
        for (int j = 0; j < players; j++) {
            std::cout << "\n<div>player no. " << j+1 << "</div>";
            playerHands[j].display();
            playerHands[j].scoreHand();
        }
    }
    std::cout << "\n<div><a href=\"/index.php\">Home</a> | <a href=\"/cgipoker.html\">C++ Poker</a></div>";
    std::cout << "\n<footer><p>CopyLeft 2016 Josh Roybal - all wrongs reserved</p></footer>";
    std::cout << "\n</body>";
    std::cout << "\n</html>";
    return 0;
}

// void function parses no. of players & no. of hads out of data buffer
// ps - playerstart, pf playerfinish
// hs - handstart, hf handfinish
// pstr - players no. string
// hstr - hands no. string
// substrlen - substring length
void parseData(char* data, unsigned& n, unsigned& h)
{
    // first get the no. of players
    std::string poststr(data);
    unsigned ps = poststr.find("=") + 1;
    unsigned pf = poststr.find("&") - 1;
    unsigned substrlen = pf - ps + 1;
    std::string pstr = poststr.substr(ps, substrlen);
    std::stringstream pss(pstr);
    if (!(pss >> n)) {
        std::cerr << "\nprocessing terminated, invalid no. of players\n";
        exit(1);
    }
    // now for the no. of hands
    std::string substring(poststr.substr(pf));
    unsigned hs = substring.find("=") + 1;
    unsigned hf = substring.find("&") - 1;
    substrlen = hf - hs + 1;
    std::string hstr = substring.substr(hs, substrlen);
    std::stringstream hss(hstr);
    if (!(hss >> h)) {
        std::cerr << "\nprocessing terminated, invalid no. of hands\n";
        exit(1);
    }
}
