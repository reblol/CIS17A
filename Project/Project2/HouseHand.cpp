#include <iostream>
#include <string>
#include "Hand.h"
#include "HouseHand.h"
#include "PlayerHand.h"
using namespace std;

// The functions below are just HouseHand versions of PlayerHand functions

//==============================================================================
// The function NextCard is used to pick a new random card for the house
//==============================================================================
int HouseHand::NextCard(bool card[], int newcard)
{
    bool CardDealt = true;
    do
    {
        newcard = (rand() % 52);
        if (!card[newcard])
        {
            CardDealt = false;
        }
    } while (CardDealt);
    return newcard;
}

//==============================================================================
// The function CardCountUp is used to raise the card count for the house
//==============================================================================
void HouseHand::CardCountUp()
{
    CardCount++;
}

//==============================================================================
// The ScoreHand function is used to calculate the hand score for the house
// and return it to a value for display
//==============================================================================
int HouseHand::ScoreHand()
{
    int AceCount = 0;
    int Score = 0;
    for (int Index = 0; Index < CardCount; Index++)
    {
        const int NextCard = hand[Index];
        const int Rank = NextCard % 13;
        if (Rank == 0)
        {
            AceCount++;
            Score++;
        }
        else if (Rank < 9)
        {
            Score = Score + (Rank + 1);
        }
        else
        {
            Score = Score + 10;
        }
    }
    while (AceCount > 0 && Score < 12)
    {
        AceCount--;
        Score = Score + 10;
    }
    return Score;
}

//==============================================================================
// The DisplayHouseHand function uses the function DisplayCard in a loop to 
// display all of the house's current hand cards
//==============================================================================
void HouseHand::DisplayHouseHand()
{
    for (int cardindex = 0; cardindex < CardCount; cardindex++)
    {
        const int NextCard = hand[cardindex];
        DisplayCard(NextCard);
        cout << " ";
    }
    cout << endl;
}

//==============================================================================
// The GetCardCount function is used to return the value of how many cards
// the house currently has.
//==============================================================================
int HouseHand::GetCardCount()
{
    return CardCount;
}

//==============================================================================
// The MovesDone function similarly to the PlayerHand one does the same thing
// being the addition of another move
//==============================================================================
void HouseHand::MovesDone()
{
    moves++;
}

//==============================================================================
// The GetMoves function returns the moves done value
//==============================================================================
int HouseHand::GetMoves()
{
    return moves;
}

//==============================================================================
// The DisplayHouseResults displays how many times the house has won against the
// player and how many times they've taken an action (hit) and losses
//==============================================================================
void HouseHand::DisplayHouseResults(PlayerHand player)
{
    cout << "House Results : \n"
            << "House Wins : " << player.GetLoss()
            << "\nHouse Losses : " << player.GetWin()
            << "\nHouse Moves : " << GetMoves();
}