// Derived class from Hand
#ifndef PLAYERHAND_H
#define PLAYERHAND_H
#include "Hand.h"
#include <iostream>
#include <string>
using namespace std;

class PlayerHand : public Hand
{
private:
    string username;
    string password;
    unsigned int score;
    int highest;
    int moves;
    int win;
    int loss;
public:
    void Shuffle(bool card[]);
    int NextCard(bool card[], int newcard);
    int ScoreHand();
    string GetName();
    int GetScore();
    void BetScore(int bet);
    void BetScorePlus(int bet);
    void DisplayPlayerHand();
    int GetCardCount();
    void HighestCheck();
    int GetHighScore();
    void Reset();
    virtual void MovesDone();
    virtual int GetMoves();
    void Final();
    
    // Class Constructor
    PlayerHand(string un, string pw, unsigned int sc) : Hand()
    {
        username = un;
        password = pw;
        score = sc;
        moves = 0;
        win = 0;
        loss = 0;
        highest = 1000;
        cout << "User registered.\n";
    }
    
    // = Operator used to copy another class's stats into the current one
    const PlayerHand operator=(const PlayerHand &right)
    {
        if (this!=&right)
        {
            username = right.username;
            password = right.password;
            score = right.score;
        }
        return *this;
    }
    
    void CardCountUp()
    {
        CardCount++;
    }
    
    void WinPlus()
    {
        win++;
    }
    
    void LossPlus()
    {
        loss++;
    }
    
    int GetWin()
    {
        return win;
    }
    
    int GetLoss()
    {
        return loss;
    }
    
    // ++ Operator used to give a pity 1 score for anyone who reaches 0
    const PlayerHand operator++()
    {
        // bonus 1 in case score is 0 for results
        if (score == 0)
        {
            ++score;
        }
    return *this;
    }
    
    // Friends
    friend ostream & operator << (ostream &out, const PlayerHand &p);
};

// << operator used to show the final results after ending the game
inline ostream & operator << (ostream &out, const PlayerHand &p)
{
    out << "Final results : \n";
    out << "Name : " << p.username << endl;
    out << "Final Score : $" << p.score << endl;
    out << "High Score : $" << p.highest << endl;
    out << "Moves Done : " << p.moves << endl;
    return out;
}

#endif /* PLAYERHAND_H */

