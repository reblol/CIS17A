//==================================================================================\\
// Name : Amine Ouaddi                                                              \\
// Class : CIS17A Fall 2022                                                         \\
// Project 1 : Blackjack                                                            \\
// Purpose : This project is a showcase of the many concepts we've learned so far.  \\
// Concepts : Pointers, Structures, C-Strings, Binary Files                         \\
//==================================================================================//
// Libraries & Namespace
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
using namespace std;

// AI & Player Hand Structure
struct Hand
{
    int Hand; // Used to receive card numbers
};

// Player Structure
struct Player
{
    string username; // Username for input
    string password; // Password for input
    unsigned int score; // Variable to collect the user's score
    Hand PlayerHand[12]; // Nested Array Structure of the player's hand
    Hand HouseHand[12]; // Nested Array Structure of the AI's hand
};

// Prototypes

void login(Player *, bool CardsDealt[]);
void shuffle(bool CardsDealt[]);
int nextcard(bool CardsDealt[], int *);
int PlayerScoreHand(Player *, const int CardCount);
int HouseScoreHand(Player *, const int CardCount);
void DisplayCard(int Card);
void DisplayPlayerHand(Player *, const int CardCount);
void DisplayHouseHand(Player *, const int CardCount);
void scores(Player *,fstream &);
void game(Player *,bool CardsDealt[], int HouseCardCount, int PlayerCardCount);

// Main
int main()
{
    // Declarations
    bool CardsDealt[52];
    Player user;
    
    // Function Start
    login(&user, CardsDealt);

    return 0;
}

//==============================================================================
// void login is used to log the user onto the game using one of the usernames
// and passwords in data.dat and start the game
//==============================================================================
void login(Player *p1, bool CardsDealt[])
{
    // Declarations
    int HouseCardCount = 0;
    int PlayerCardCount = 0;
    fstream data;
    string userandpass, line;
    bool check = false;
    
    // Login Program
    cout << "||==================||" << endl
         << "||     Blackjack    ||" << endl
         << "||==================||" << endl;
    
    // Name & Password 
    cout << "Username : ";
    getline(cin, p1->username);
    cout << "\nPassword : ";
    getline(cin, p1->password);
    
    userandpass = p1->username + " " + p1->password;
    p1->score = 1000;
    
    //File Opening
    data.open("data.dat", ios::in);
    
    // User Validation
    while (getline(data, line) && !check)
    {
        if (line.compare(userandpass) == 0)
        {
            check = true;
            cout << "\nWelcome " << p1->username << "!" << endl;
        }
    }
    
    // User not found
    if (!check)
    {
       cout << "Username or password not found in the database. Run the program again to retry.\n";
       exit(0);
    }
    data.close();
    game(p1,CardsDealt,HouseCardCount,PlayerCardCount);
}

//==============================================================================
// void game is the main function and serves as the base for all the others
// it uses every function underneath to start a game of blackjack, shuffle cards
// show player cards, house cards and save scores onto a file
//==============================================================================
void game(Player *p1,bool CardsDealt[], int HouseCardCount, int PlayerCardCount)
{
    // Random Numbers
    time_t qTime;
    time(&qTime);
    srand(qTime);
    
    
    // Declarations
    fstream score;
    int NewCard;
    int *ptr = nullptr;
    ptr = &NewCard;
    bool flag = true;
    int bets;
    
    // Main Loop
    while (flag == true)
    {
        // Shuffling Cards
        shuffle(CardsDealt);
        
        // Player & House first two cards
        p1->PlayerHand[0].Hand = nextcard(CardsDealt, ptr);
        p1->HouseHand[0].Hand = nextcard(CardsDealt, ptr);
        p1->PlayerHand[1].Hand = nextcard(CardsDealt, ptr);
        p1->HouseHand[1].Hand = nextcard(CardsDealt, ptr);
        HouseCardCount = 2;
        PlayerCardCount = 2;
        
        // More Declarations
        char PlayerChoice;
        bool PlayerHits = true;
        
        // Player Score
        int PlayerScore = PlayerScoreHand(p1,PlayerCardCount);
        
        // Game Start
        cout << "Welcome to Blackjack!\n";
        cout << p1->username << " Balance : $" << p1->score << endl;
        
        cout << "Place a bet.\n";
        cout << "Bet : ";
        cin >> bets;
        
        // Validation
        
        while (bets > p1->score)
        {
            cout << "Invalid bet. Please try again.\n";
            cin >> bets;
        }
        if (bets == 0 || p1->score == 0) // No Money = Auto Shutdown
        {
            cout << "\nNot enough money. Restart the program to login again.";
            scores(p1,score);
            exit(0);
        }
        
        // Bet Start
        cout << "||=========================||\n";
        cout << "||        Blackjack        ||\n";
        cout << "||=========================||\n";
        
        // Bet Taken & Money Remaining
        p1->score = p1->score - bets;
        
        cout << "//Money remaining : $" << p1->score << endl;
        cout << "//Current Bet : $" << bets << endl << endl;
        // Hands Display
        do 
        { // Starting Hands
            cout << "||  House Hand  ||\n";
            cout << "** || ";
            DisplayCard(p1->HouseHand[1].Hand);
            cout << endl;
            cout << "|| Player Hand ||\n";
            cout << "\\ Score : " << PlayerScoreHand(p1,PlayerCardCount) << endl;
            DisplayPlayerHand(p1,PlayerCardCount);
            
            // Hit or Stay
            cout << "Choose an option :\nH) Hit\nS) Stay\n";
            cin >> PlayerChoice;
            
            // Option Ifs
            if (PlayerChoice == 'h') // HIT
            {
                p1->PlayerHand[PlayerCardCount].Hand = nextcard(CardsDealt, ptr);
                ++PlayerCardCount;
            }
            else if (PlayerChoice == 's') // STAY
            {
                PlayerHits = false;
            }
            else // Invalid Input
            {
                cout << "Invalid Input. Try again.\n";
            }
            PlayerScore = PlayerScoreHand(p1,PlayerCardCount);
        }while (PlayerHits && PlayerScore < 22);
        
        // Score Checks
        if (PlayerScore > 21)                     // PLAYER BUSTS
        {
            cout << "Winner : House\n";
            cout << "You lost $" << bets << endl;
        }
        else
        {
            int HouseScore = HouseScoreHand(p1, HouseCardCount); // HOUSE AI 
            while (HouseScore < 17)
            {
                p1->HouseHand[HouseCardCount].Hand = nextcard(CardsDealt, ptr);
                HouseCardCount++;
                HouseScore = HouseScoreHand(p1, HouseCardCount);
            }
            bool HouseBust =  (HouseScore > 21);
            if (HouseBust)                                      // HOUSE BUSTS
            {
                cout << "House Busted!\n";
                cout << "Winner : " << p1->username << endl;
                bets = bets * 2;
                cout << "You gained $" << bets << endl;
                p1->score = bets + p1->score;
            }
            else
            {
                if (PlayerScore == HouseScore)                // TIE (PUSH)
                {
                    cout << "Push!\n";
                    cout << "No money gained." << endl;
                    p1->score = bets + p1->score;
                    
                }
                else if (PlayerScore > HouseScore)            // PLAYER WINS
                {
                    cout << "Winner : " << p1->username << endl;
                    bets = bets * 2;
                    cout << "You gained $" << bets << endl;
                    p1->score = bets + p1->score;
                }
                else 
                {
                    cout << "Winner : House\n";
                    cout << "You lost $" << bets << endl;
                }
            }
        }
        // Continue Declaration & Input Validation
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
            flag = false;
            scores(p1,score);
        }
        else // Another game
        {
            flag = true;
        }
    }
}

//==============================================================================
// void shuffle is used to shuffle cards by a for loop of the cardsDealt boolean
//==============================================================================
void shuffle(bool CardsDealt[])
{
    // Shuffle Bool
    for (int Index = 0; Index < 52; Index++)
    {
        CardsDealt[Index] = false;
    }
}

//==============================================================================
// int NextCard is the function used for the hit option in blackjack
//==============================================================================
int nextcard(bool CardsDealt[], int *NewCard)
{
    bool CardDealt = true; // Random Card Loop
    do
    {
        *NewCard = (rand() % 52);
        if (!CardsDealt[*NewCard])
        {
            CardDealt = false;
        }
    } while (CardDealt);
    return *NewCard;
}

//==============================================================================
// int PlayerScoreHand is a function used to get the player's hand score and
// return it to the score integer
//==============================================================================
int PlayerScoreHand(Player *p1, const int CardCount)
{
    // Declarations & Score Loop
    int AceCount = 0;
    int Score = 0;
    for (int Index = 0; Index < CardCount; Index++)
    {
        const int NextCard = p1->PlayerHand[Index].Hand;
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
// int HouseScoreHand is the same as PlayerScoreHand except that it's for the 
// house part of the p1 structure
//==============================================================================
int HouseScoreHand(Player *p1, const int CardCount)
{
    // Declarations
    int AceCount = 0;
    int Score = 0;
    // Score Loop
    for (int Index = 0; Index < CardCount; Index++)
    {
        const int NextCard = p1->HouseHand[Index].Hand;
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
// void DisplayCard is used to display the card itself using C-Strings
//==============================================================================
void DisplayCard(int Card)
{
    // C-Strings & Length
    char Ace[] = "Ace";
    char Ten[] = "Ten";
    char Jack[] = "Jack";
    char Queen[] = "Queen";
    char King[] = "King";
    int length;
    
    // Display Rank & Suit
    const int RANK = (Card % 13);
    
    // Rank length output loops
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
    
    // Suits Ifs
    const int Suit = Card / 13;
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

//==============================================================================
// void DisplayPlayerHand is a loop of DisplayCard to display the entirety of 
// the player's deck
//==============================================================================
void DisplayPlayerHand(Player *p1, const int CardCount)
{
    // Loop for the DisplayCard function
    for (int cardindex = 0; cardindex < CardCount; cardindex++)
    {
        const int NextCard = p1->PlayerHand[cardindex].Hand;
        DisplayCard(NextCard);
        cout << " ";
    }
    cout << endl;
}

//==============================================================================
// void DisplayHouseHand is a loop of DisplayCard to display the entirety of the
// house's hand
//==============================================================================
void DisplayHouseHand(Player *p1, const int CardCount)
{
    // Loop to Display the house's hand
    for (int cardindex = 0; cardindex < CardCount; cardindex++)
    {
        const int NextCard = p1->HouseHand[cardindex].Hand;
        DisplayCard(NextCard);
        cout << " ";
    }
    cout << endl;
}

//==============================================================================
// void scores is a function used to get the user's score as in money total at
// the end of the game and save it into a the score.txt file in a stack format
// making it possible to re-run the program and not worry about the text being
// overwritten.
//==============================================================================
void scores(Player *p1,fstream &score)
{
    // File Opening
    score.open("score.txt",ios::out | ios::app);
    // Formatting & Seeking file end
    score << setprecision(0);
    score.seekp(0L, ios::end);
    // Input to file
    score << "Username : " << p1->username << "\t" << "|| Final Score : " << p1->score << endl;
    score << "|| ";
    // Closure
    score.close();
}