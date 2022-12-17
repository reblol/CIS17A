#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "PlayerHand.h"
#include "Hand.h"
using namespace std;
//==============================================================================
// The function below is used to shuffle the player's cards
//==============================================================================
void PlayerHand::Shuffle(bool card[])
    {
        cout << "Shuffling Cards...\n";
        for (int index = 0; index < 52; index++)
            {
                card[index] = false;
            }
    }

//==============================================================================
// The function NextCard is used to generate a new card for the player's deck
//==============================================================================
int PlayerHand::NextCard(bool card[], int newcard)
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
// The function ScoreHand is used to calculate the player's cards score (hand)
//==============================================================================
int PlayerHand::ScoreHand()
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
// The function GetName is used to return the player's username
//==============================================================================
string PlayerHand::GetName()
{
    return username;
}

//==============================================================================
// The function GetScore is used to return the player's money amount
//==============================================================================
int PlayerHand::GetScore()
{
    return score;
}

//==============================================================================
// The function BetScore is used to take away the bet from the player's money
//==============================================================================
void PlayerHand::BetScore(int bet)
{
    score -= bet;
}

//==============================================================================
// The function DisplayPlayerHand is used to display all of the player's cards
//==============================================================================
void PlayerHand::DisplayPlayerHand()
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
// The function GetScore is used to return the player's card count
//==============================================================================
int PlayerHand::GetCardCount()
{
    return CardCount;
}

//==============================================================================
// The function GetScore is used after the player wins a round to get his bet
// money.
//==============================================================================
void PlayerHand::BetScorePlus(int bet)
{
    score += bet;
}

//==============================================================================
// The function Reset is used to bring back the card count to 0
//==============================================================================
void PlayerHand::Reset()
{
    CardCount = 0;
}

//==============================================================================
// The function MovesDone adds up the player's moves
//==============================================================================
void PlayerHand::MovesDone()
{
    moves++;
}

//==============================================================================
// The function GetMoves returns the player's moves variable
//==============================================================================
int PlayerHand::GetMoves()
{
    return moves;
}

//==============================================================================
// The function Final saves the player's stats into the score.txt file
//==============================================================================
void PlayerHand::Final()
{
    fstream scores;
    // File Opening
    scores.open("score.txt",ios::out | ios::app);
    // Formatting & Seeking file end
    scores << setprecision(0);
    scores.seekp(0L, ios::end);
    // Input to file
    scores << "\n=====================================\n"
            << "Username : " << username
            << "\nHigh Score : $" << GetHighScore()
            << "\nFinal Score : $" << GetScore()
            << "\nMoves Done : " << GetMoves()
            << "\nWins : " << GetWin()
            << "\nLosses : " << GetLoss()
            << "\n=====================================\n";
    // Closure
    scores.close();
}

//==============================================================================
// The Function HighestCheck is used to compare the player's current score with
// the highest one starting with 1000 and replacing it with the current score if
// higher. This variable will be used later in displaying the final results
//==============================================================================
void PlayerHand::HighestCheck()
{
    if (highest < score)
    {
        highest = score;
    }
}

//==============================================================================
// The Function GetHighScore is used to return the highest score value. This is
// used in the final results display after the game is over. In addition, also
// it is saved in the score.txt file for data of previous games
//==============================================================================
int PlayerHand::GetHighScore()
{
    return highest;
}