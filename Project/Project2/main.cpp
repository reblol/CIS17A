//====================================================
// Name : Amine Ouaddi
// Assignment : CIS-17A Project 2
// Class : CIS-17A
// Notes : 
// There are only a few bugs in this project I'd like to point out
// 1 is the destructor, I was going to use it to delete the class instance
// when exited but it for some reason starts randomly during the program
// therefore I had no way of using it other than to output messages
// 2 is an Input bug I've had since the first iteration of this project
// When selecting an action with the numbers sometimes the game will freeze
// into this input loop where you are able to input an answer but will not
// be given a response and the only way out is to shut it down and re-run it
// I've tried going from chars, integers, and strings but none of them worked.
// I haven't tried running the code in any other IDE but maybe it'll run better
// through VSCode or others.
// DISPLAY OF CONCEPTS
// Exceptions - line 62 - line 123 - line 171
// Virtual Functions - PlayerHand.h line 32 - Hand.h line 25 - HouseHand.h - line 20
// Classes - PlayerHand.h - Hand.h - HouseHand.h
// Operator Overloading - PlayerHand.h lines 50, 87, 102
// Templates - line 40
//====================================================
// Libraries
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include "Hand.h"
#include "PlayerHand.h"
#include "HouseHand.h"
using namespace std;

// Function Prototypes 

void LoginCheck(bool check, string userandpass, string line, string username, fstream &data);
void BetValidation(int bets, PlayerHand Player);
void ActionValidation(int PlayerChoice, PlayerHand Player, bool PlayerHits, bool CardsDealt, int NewCard);

// Template

template <class T>
T betdouble(T number)
{
    return number * 2;
}

// Main Code

int main()
{
    // Declarations
    bool CardsDealt[52];
    int HouseCardCount = 0;
    fstream data;
    string userandpass, line;
    string username;
    string password;
    unsigned int score;
    bool check = false;
    bool tryAgain = true;
    cout << "||====================||\n"
         << "||      Blackjack     ||\n"
         << "||====================||\n";
    // Exception Menu Loop
    while (tryAgain)
    {
        try // Try 
        {
            // Input & Output Login
            cout << "|| Username : ";
            getline(cin, username);
            cout << "\n|| Password : ";
            getline(cin, password);
            userandpass = username + " " + password;
            score = 1000;
            LoginCheck(check, userandpass, line, username, data);
            cout << "Welcome " << username << " !\n";
            tryAgain = false; // Loop Off
        }
        catch (string exit) // Error Catch
        {
            cout << exit; // Error Message Output
        }
    }
    
    // Classes Initialization
    PlayerHand Player(username, password, score);
    HouseHand House;
    
    // Random Sequencers
    time_t qTime;
    time(&qTime);
    srand(qTime);
    
    // More Variable Declarations
    int NewCard;
    bool flag = true;
    int bets;
    
    // Main Game Loop
    
    while (flag)
    {
        // First two cards given to both player & house
        Player.Reset();
        Player.Shuffle(CardsDealt);
        Player.hand[0] = Player.NextCard(CardsDealt,NewCard);
        Player.CardCountUp();
        House.hand[0] = House.NextCard(CardsDealt, NewCard);
        House.CardCountUp();
        Player.hand[1] = Player.NextCard(CardsDealt,NewCard);
        Player.CardCountUp();
        House.hand[1] = House.NextCard(CardsDealt, NewCard);
        House.CardCountUp();
        
        // More Variable Declarations
        bool PlayerHits = true;
        bool BetAgain = true;
        int PlayerScore = Player.ScoreHand();
        bool PlayerSurrender = false;
        
        // Welcome Message & Balance Check
        cout << "\nWelcome to Blackjack!\n";
        cout << Player.GetName() << " Balance : $" << Player.GetScore() << endl;
        
        // Bet Input Exception Loop
        while (BetAgain)
        {
            try
            {
                cout << "Place a bet : \n";
                cout << "Bet : ";
                cin >> bets;
                BetValidation(bets, Player);
                BetAgain = false;
            }
            catch (string error1)
            {
                cout << error1;
            }
        }
        
        cout << "||=========================||\n";
        cout << "||        Blackjack        ||\n";
        cout << "||=========================||\n";
        
        // Decrease score by bet amount
        Player.BetScore(bets);
        
        // Money remaining and bet output
        cout << "//Money remaining : $" << Player.GetScore() << endl;
        cout << "//Current Bet : $" << bets << endl << endl;
        
        // Action Loop
        
        do
        {
            cout << "|| House Hand : \n"
                    << "|| ";
            House.DisplayCard(1);
            cout << endl;
            cout << "|| Player Hand : \n"
                    << "|| Score : " << Player.ScoreHand() << endl;
            cout << "|| ";
            Player.DisplayPlayerHand();
            
            int PlayerChoice;
            bool Valid = true;
            
            // Action Exceptions
            // There is a bug I have not been able to fix in the actions
            // sometimes when inputting the right number for the action
            // the code afterwards would not run and would loop back to the cin
            // infinitely, however this rarely happens.
            while (Valid)
            {
                try
                {
                    cout << "Choose an option :\n"
                            << "1|| Hit\n"
                            << "2|| Stand\n"
                            << "3|| Double Down\n"
                            << "4|| Surrender\n"
                            << endl;
                    cin >> PlayerChoice;
                    ActionValidation(PlayerChoice, Player, PlayerHits, CardsDealt, NewCard);
                    Valid = false;
                }
                // Error Catch Statement
                catch (string error3)
                {
                    cout << error3;
                }
                // The next catches work similarly to how an If statement would
                // The first one is a Hit If
                catch (int player1)
                {
                    Valid = false;
                    Player.MovesDone();
                    int holder = Player.GetCardCount();
                    Player.hand[holder] = Player.NextCard(CardsDealt, NewCard);
                    Player.CardCountUp();
                    PlayerSurrender = false;
                }
                // Stay/Stand If
                catch (char player2)
                {
                    PlayerHits = false;
                    Valid = false;
                    Player.MovesDone();
                    PlayerSurrender = false;
                }
                // Double Down If
                catch (bool player3)
                {
                    // To double on the bet amount we must first
                    // take out the second amount of the bet from the score
                    // therefore using .BetScore for a second time
                    Player.BetScore(bets);
                    bets = betdouble(bets);
                    Player.MovesDone();
                    int holder = Player.GetCardCount();
                    Player.hand[holder] = Player.NextCard(CardsDealt, NewCard);
                    Player.CardCountUp();
                    PlayerHits = false;
                    Valid = false;
                    PlayerSurrender = false;
                }
                // Surrender If
                catch (float player4)
                {
                    bets = bets / 2;
                    Player.BetScorePlus(bets);
                    PlayerHits = false;
                    Valid = false;
                    PlayerSurrender = true;
                }
            }
            // Card Score Updated
            PlayerScore = Player.ScoreHand();
        } while (PlayerHits && PlayerScore < 22);
        
        // Win Ifs
        
        // Player Bust If
        if (PlayerScore > 21 && !PlayerSurrender)
        {
            Player.LossPlus();
            cout << "Winner : House\n";
            cout << "You lost $" << bets << endl;
        }
        else if (PlayerSurrender)
        {
            cout << "Player surrendered.\n";
            cout << "Bet split.\n";
        }
        else
        {
            // House AI Below
            int HouseScore = House.ScoreHand(); 
            while (HouseScore < 17) // Hit when under 17
            {
                int holder2 = House.GetCardCount();
                House.hand[holder2] = House.NextCard(CardsDealt, NewCard);
                House.MovesDone();
                HouseCardCount++;
                HouseScore = House.ScoreHand();
            }
            // House Bust declaration
            bool HouseBust =  (HouseScore > 21);
            // House Bust If
            if (HouseBust)                                      
            {
                // The functions below are used to register both player moves
                // and player win interactions with the AI.
                Player.WinPlus();
                House.MovesDone();
                cout << "House Busted!\n";
                cout << "Winner : " << Player.GetName() << endl;
                bets = betdouble(bets);
                cout << "You gained $" << bets << endl;
                Player.BetScorePlus(bets);
            }
            else
            {
                // Tie (Push)
                if (PlayerScore == HouseScore)  
                {
                    cout << "Push!\n";
                    cout << "No money gained." << endl;
                    Player.BetScorePlus(bets);
                    
                }
                // Player Wins
                else if (PlayerScore > HouseScore)
                {
                    Player.WinPlus();
                    cout << "Winner : " << Player.GetName() << endl;
                    bets = betdouble(bets);
                    cout << "You gained $" << bets << endl;
                    Player.BetScorePlus(bets);
                }
                // House Wins
                else 
                {
                    cout << "Winner : House\n";
                    Player.LossPlus();
                    cout << "You lost $" << bets << endl;
                }
            }
        }
        // Continue Output & Input
        char again;
        cout << "Continue? Y/N\n";
        cin >> again;
        while (!((again == 'y') ||(again == 'n')))  // Validation
        {
            cout << "Invalid Input. Try again.";
            cout << "Continue? Y/N\n";
            cin >> again;
        }
        if (again == 'n') // Quit If & Score Saved
        {
            // Another PlayerHand instance is created to reset the player
            // data through the = operator
            // The destructor was planned to be used to delete the class instead
            // but it won't run as wanted.
            flag = false;
            PlayerHand holder("empty", "empty", 0);
            // The overloaded increment operator is also used for a pity 1 score
            // registration incase the player score is 0
            if (Player.GetScore() <= 0)
            {
                ++Player;
            }
            // the function below saves all of the players stats into the score.txt
            // file.
            Player.Final();
            // The overloaded << operator is used to show the results of the
            // game session.
            cout << Player;
            House.DisplayHouseResults(Player);
            Player = holder;
        }
        else // Another game
        {
            flag = true;
        }
    }
}

//==============================================================================
// The LoginCheck function is used to validate the login information through
// comparison with the data.dat file. If not then an error message will be 
// thrown.
//==============================================================================
void LoginCheck(bool check, string userandpass, string line, string username, fstream &data)
{
    data.open("data.dat", ios::in);
    while (getline(data, line) && !check)
    {
        if (line.compare(userandpass) == 0)
        {
            check = true;
            data.close();
        }
    }
    
    // User not found
    if (!check)
    {
        data.close();
       string exit = "ERROR : Username or Password not found.\n";
       throw exit;
    }
}

//==============================================================================
// The BetValidation function is used to validate the player's bet amount.
// If it equals 0 however the program will stop running as there is no way to
// gain more money.
//==============================================================================
void BetValidation(int bets, PlayerHand Player)
{
    string error1 = "ERROR 1 : Invalid Bet Amount. Type a valid amount between your range.\n";
    string error2 = "ERROR 2 : Player does not have a valid amount of money to bet.\n";
    if (bets > Player.GetScore())
        {
            throw error1;
        }
    if (bets == 0 || Player.GetScore() == 0)
        {
            cout << error2;
            PlayerHand holder("empty", "empty", 0);
            ++Player;
            Player.Final();
            Player = holder;
            exit(0);
        }
}

//==============================================================================
// The ActionValidation function is used to validate the player's action during
// the game, the throws in this function are used more akin to an If statement
// rather than an error return except for the final else statement.
//==============================================================================
void ActionValidation(int PlayerChoice, PlayerHand Player, bool PlayerHits, bool CardsDealt, int NewCard)
{
    if (PlayerChoice == 2) // HIT
        {
            char player2 = '2';
            throw player2;
        }
    else if (PlayerChoice == 1) // STAY
        {
            int player1 = 0;
            throw player1;
        }
    else if (PlayerChoice == 3)
    {
        bool player3 = true;
        throw player3;
    }
    else if (PlayerChoice == 4)
    {
        float player4 = 4;
        throw player4;
    }
    else
        {
            string error3 = "ERROR : Invalid Input. Type a valid value.\n";
            throw error3;
        }
}
