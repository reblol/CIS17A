#ifndef HOUSEHAND_H
#define HOUSEHAND_H
#include "Hand.h"
#include "PlayerHand.h"
#include <iostream>
using namespace std;

// Derived Class from Hand, different from PlayerHand but using similar functions
class HouseHand : public Hand
{
    // the biggest difference is that the house hand doesn't include alot of
    // data values such as the username, password as it is an AI
private:
    int moves = 0;
public:
    // the only functions available for the house are used for it's AI
    // to either pick a card, display the hand and get results.
    int NextCard(bool card[], int newcard);
    int ScoreHand();
    void CardCountUp();
    int GetCardCount();
    void DisplayHouseHand();
    void DisplayHouseResults(PlayerHand player);
    virtual void MovesDone();
    virtual int GetMoves();
    
};


#endif /* HOUSEHAND_H */

