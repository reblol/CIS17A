#include "Hand.h"
#include "HouseHand.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

//==============================================================================
// This function is used to display a singular card from the player's deck
// it is used in other functions in loops to display the entire player's hand
//==============================================================================
void Hand::DisplayCard(int index)
{
    char Ace[] = "Ace";
    char Ten[] = "Ten";
    char Jack[] = "Jack";
    char Queen[] = "Queen";
    char King[] = "King";
    int length;
    
    unsigned int RANK = (hand[index] % 13);
    
    if (RANK == 0) 
    {
        length = strlen(Ace);
        for (int i = 0; i < length; i++)
        {
           cout << Ace[i];
        }
    }
    else if (RANK < 9) 
    {
	cout << (RANK + 1);
    }
    else if (RANK == 9) 
    {
        length = strlen(Ten);
        for (int i = 0; i < length; i++)
        {
            cout << Ten[i];
        }
    }
    else if (RANK == 10) 
    {
        length = strlen(Jack);
        for (int i = 0; i < length; i++)
        {
            cout << Jack[i];
        }
    }
    else if (RANK == 11) 
    {
        length = strlen(Queen);
        for (int i = 0; i < length; i++)
        {
            cout << Queen[i];
        }
    }
    else 
    {
        length = strlen(King);
        for (int i = 0; i < length; i++)
        {
            cout << King[i];
        }
    }
    
    const int Suit = hand[index] / 13;
    if (Suit == 0)
    {
        cout << " Of Clubs || ";
    }
    else if (Suit == 1)
    {
        cout << " Of Diamonds || ";
    }
    else if (Suit == 2)
    {
        cout << " Of Hearts || ";
    }
    else
    {
        cout << " Of Spades || ";
    }
}