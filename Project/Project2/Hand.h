#ifndef HAND_H
#define HAND_H
#include <iostream>
using namespace std;

// Base class for both PlayerHand and HouseHand

class Hand
{
    // Protected variable to be shared with derived classes
protected:
    int CardCount;
public:
    int hand[12];
    // Functions available to derived classes including two virtual functions
    void DisplayCard(int index);
    virtual void MovesDone() = 0;
    virtual int GetMoves() = 0;
    // Constructor initialized after the derived class's constructor
    Hand() 
    {
        CardCount = 0;
    }
    // the destructors are called for after the object goes out of scope
    virtual ~Hand()
    {
        cout << "...\n";
    }
};

#endif /* HAND_H */

