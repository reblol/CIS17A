// THIS VERSION OF BLACKJACK IS UNFINISHED
// WHEN THE GAME FUNCTION RUNS IT WILL KEEP LOOPING INFINITELY
// IT LACKS THE SCORE FUNCTION AND MORE CODE IN THE GAME FUNCTION
// IN ADDITION TO A LACK OF COMMENTS
// Name : Amine Ouaddi
// Class : CIS17A
// Project 1 : <Blackjack>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

struct Hand
{
    int Hand;
};

struct Player
{
    string username;
    string password;
    unsigned int score;
    Hand PlayerHand[12];
    Hand HouseHand[12];
};

void login(Player *, bool CardsDealt[]);
void shuffle(bool CardsDealt[]);
int nextcard(bool CardsDealt[], int *);
int PlayerScoreHand(Player *, const int CardCount);
int HouseScoreHand(Player *, const int CardCount);
void DisplayCard(int Card);
void DisplayPlayerHand(Player *, const int CardCount);
void DisplayHouseHand(Player *, const int CardCount);
void game(Player *,bool CardsDealt[], int HouseCardCount, int PlayerCardCount);

int main()
{
    // Declarations
    bool CardsDealt[52];
    Player user;
    
    // Function
    login(&user, CardsDealt);

    return 0;
}

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
    // Closure & Game Starting
    data.close();
    game(p1,CardsDealt,HouseCardCount,PlayerCardCount);
    
    // User not found
    if (!check)
    {
       cout << "Username or password not found in the database. Run the program again to retry.\n";
       exit(0);
    }
}

void game(Player *p1,bool CardsDealt[], int HouseCardCount, int PlayerCardCount)
{
    // Random Numbers
    time_t qTime;
    time(&qTime);
    srand(qTime);
    
    
    // Declarations
    int NewCard;
    int *ptr = nullptr;
    ptr = &NewCard;
    bool flag = true;
    int choice = 1;
    int bets;
    
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
        
        char PlayerChoice;
        bool PlayerHits = true;
        
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
            if (bets == 0 || p1->score == 0)
            {
              cout << "\nNot enough money.";
              exit(0);
            }
        }
        
        cout << "||=========================||\n";
        cout << "||        Blackjack        ||\n";
        cout << "||=========================||\n";
        
        p1->score = p1->score - bets;
        
        cout << "//Money remaining : $" << p1->score << endl;
        cout << "//Current Bet : $" << bets << endl << endl;
        do 
        {
            cout << "||  House Hand  ||\n";
            cout << "** || ";
            DisplayCard(p1->HouseHand[1].Hand);
            cout << endl;
            cout << "|| Player Hand ||\n";
            cout << "\\ Score : " << PlayerScoreHand(p1,PlayerCardCount) << endl;
            DisplayPlayerHand(p1,PlayerCardCount);
        } 
    }
}

void shuffle(bool CardsDealt[])
{
    for (int Index = 0; Index < 52; Index++)
    {
        CardsDealt[Index] = false;
    }
}

int nextcard(bool CardsDealt[], int *NewCard)
{
    bool CardDealt = true;
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

int PlayerScoreHand(Player *p1, const int CardCount)
{
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

int HouseScoreHand(Player *p1, const int CardCount)
{
    int AceCount = 0;
    int Score = 0;
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

void DisplayCard(int Card)
{
    char Ace[] = "Ace";
    char Ten[] = "Ten";
    char Jack[] = "Jack";
    char Queen[] = "Queen";
    char King[] = "King";
    int length;
    
    // Display Rank & Suit
    const int RANK = (Card % 13);
    
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

void DisplayPlayerHand(Player *p1, const int CardCount)
{
    for (int cardindex = 0; cardindex < CardCount; cardindex++)
    {
        const int NextCard = p1->PlayerHand[cardindex].Hand;
        DisplayCard(NextCard);
        cout << " ";
    }
    cout << endl;
}

void DisplayHouseHand(Player *p1, const int CardCount)
{
    for (int cardindex = 0; cardindex < CardCount; cardindex++)
    {
        const int NextCard = p1->HouseHand[cardindex].Hand;
        DisplayCard(NextCard);
        cout << " ";
    }
    cout << endl;
}