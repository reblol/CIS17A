// OLDEST VERSION OF THE PROJECT
// DESPITE SEEMING COMPLETE THIS VERSION IS BUGGY AND LACKS THE INCLUSION OF MANY OF THE CONCEPTS
// THE NEWER VERSION INCLUDES ALL CONCEPTS LEARNED SO FAR
// Name : Amine Ouaddi
// Class : CIS17A
// Project : Blackjack
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

struct Player
{
    string username;
    unsigned int score;
};
void scores(Player *users);
void shuffle(bool CardsDealt[]);
void displayCard(int Card);
void displayHand(int hand[], const int CardCount);
void displayScoresAndHands(int HouseHand[],int PlayerHand[], const int HouseCardCount, const int PlayerCardCount);
int nextCard(bool CardsDealt[], int N);
int scoreHand(int hand[], const int CardCount);
void accountlogin(Player *users, bool CardsDealt[],int hhand[],int phand[], int hcardcount, int pcardcount);
void game(bool CardsDealt[],int HouseHand[], int PlayerHand[], int hcardcount, int pcardcount, Player *users);

int main()
{
    time_t qTime;
    time(&qTime);
    srand(qTime);
    // Variable Declaration
    bool CardsDealt[52];
    int HCardCount = 0;
    int HHand[12];
    int PCardCount = 0;
    int PHand[12];
    Player users;
    
    // Game starts off with a user login menu
    accountlogin(&users, CardsDealt, HHand, PHand, HCardCount, PCardCount);
    

}

void accountlogin(Player *users, bool CardsDealt[],int hhand[], int phand[], int hcardcount, int pcardcount)
{
    // Initiation Variables
    fstream data;
    fstream score;
    string usernpass, line;
    string password;
    string username;
    char option;
    bool found = false;
    
    // Starting Display
    
    cout << "//===========================\\" << endl;
    cout << "||         Blackjack         ||" << endl;
    cout << "\\===========================//\n" << endl;
    
    // Option Display
    
    cout << "Select an option from the menu below." << endl;
    cout << "1 - Sign up" << endl;
    cout << "2 - Login" << endl;
    cout << "3 - Quit" << endl;
    cin >> option;
    
    // Option Switch
    
    switch (option)
    {
        case'1': // New User
        {
            cout << "//=========================\\" << endl;
            cout << "||  New user registration  ||" << endl;
            cout << "\\=========================//" << endl << endl;
            
            // File Opening
            
            data.open("userdata.dat", ios::app);
            score.open("userscore.dat", ios::app);
            
            // Name Input & Output
            
            cout << "Username : ";
            cin >> username;
            
            // Structure Input
            
            users->username = username;
            users->score = 1000;
            
            // Password Input & Output
            
            cout << "Password : ";
            cin >> password;
            
            // File Input
            
            data << username << " " << password << endl;
            score << username << endl << users->score << endl;
            
            // Closure
            
            data.close();
            score.close();
            
            // Registration
          
            cout << "User registered!" << endl;
            game(CardsDealt,hhand,phand,hcardcount,pcardcount,users);
            break;
        }
        case'2': // Existing User
        {
            cout << "//=========================\\" << endl;
            cout << "||   Existing user login   ||" << endl;
            cout << "\\=========================//" << endl;
            
            // File Opening
            
            data.open("userdata.dat", ios::in);
            
            // Username & Password Output & Input
            
            cout << "Username : ";
            cin >> username;
            cout << "\nPassword : ";
            cin >> password;
            users->username = username;
            
            // String to validate existing data in file
            
            usernpass = username + " " + password;
            
            // Data Validation
            
            if (data.is_open())
            {
                while (getline(data, line) && !found) {
                    if (line.compare(usernpass) == 0)
                    {
                        found = true; // Username & Password are the same in the files
                    }
                }
                data.close();
                if (found) {
                    cout << "\nWelcome " << username << "!\n" << endl; // Welcome message
                    game(CardsDealt,hhand,phand,hcardcount,pcardcount,users);
                }
                else // User not found
                {
                    cout << "Username and password not found in the database. Press 1 to exit. \n";
                    cin >> password;
                    if (password == "1")
                    {
                        accountlogin(users, CardsDealt, hhand, phand, hcardcount, pcardcount); //  Back to menu
                    }
                }
                found = false;
                score.open("userscore.dat", ios::in);
                if (score.is_open()) // Score user comparison
                {
                    while (getline(score, line) && !found)
                    {
                        if (line.compare(username) == 0)
                        {
                            found = true;
                            score >> users->score;
                        }
                    }
                    data.close();
                    score.close();
                }
            }
            break;
        }
        case'3':
        {
            break;
        }
        default : // Wrong Number
        {
            cout << "Wrong number. Try again.\n";
            accountlogin(users, CardsDealt, hhand, phand, hcardcount, pcardcount);
            break;
        }
    }
}

void game(bool CardsDealt[], int HouseHand[],int  PlayerHand[], int HouseCardCount, int PlayerCardCount, Player *users)
{

        int NewCard;
	bool flag = true;
	int choice = 1;
	int bets;

	// Loops for hand
	while (flag == true) {

		// Shuffles the cards
		shuffle(CardsDealt);

		// Two cards are dealt for each player and house
		PlayerHand[0] = nextCard(CardsDealt, NewCard);
		HouseHand[0] = nextCard(CardsDealt, NewCard);
		PlayerHand[1] = nextCard(CardsDealt, NewCard);
		HouseHand[1] = nextCard(CardsDealt, NewCard);
		HouseCardCount = 2;
		PlayerCardCount = 2;

		char PlayerChoice;
		bool PlayerHits = true;
		int PlayerScore = scoreHand(PlayerHand, PlayerCardCount);

		// The start of a new hand
		cout << "===========================================" << endl;
		cout << "=             Black Jack 21               =" << endl;
		cout << "===========================================" << endl;
                
		cout << users->username << "'s Money: $" << users->score << endl;
                

		cout << "Place your bets!" << endl;
		cout << "Bet: ";
		cin >> bets;
                

		while (bets > users->score) {  // Validation if user enters more money than in account
			cout << "You entered a bet more than you have in your account.\n"
				<< "Please enter your bet: ";
			cin >> bets;
                        if (bets == 0 || users->score == 0)
                        {
                            cout << "\nNot enough money.";
                            exit(0);
                        }
		}


		// The start of a new hand
		cout << "===========================================" << endl;
		cout << "=             Black Jack 21               =" << endl;
		cout << "===========================================" << endl;

		//=============================== Fix validation on money bet====================================
		users->score = users->score - bets;
		cout << "You bet: $" << bets << "	Money left: $" << users->score << endl << endl;

		// Get Player's hits. Calculate the score and redisplay after each hit.
		do {

			// Displays the dealt cards, but only the House's second card.
			cout << "House's Hand" << endl;
			cout << "** ";
			displayCard(HouseHand[1]);
			cout << endl;
			cout << "\nPlayer's Hand: Score = " << scoreHand(PlayerHand, PlayerCardCount) << endl;
			displayHand(PlayerHand, PlayerCardCount);

			// Ask the Player whether he wants a hit or to stay
				cout << "\nHit(h) or stay(s): ";
				cin >> PlayerChoice;

			if (PlayerChoice == 'h') {
				PlayerHand[PlayerCardCount]= nextCard(CardsDealt, NewCard);
				++PlayerCardCount;
			}
			else if (PlayerChoice == 's') {
				PlayerHits = false;
			}
			else {
				cout << "Error: Try Again!" << endl;
			}
			cout << endl;

			// Get the Player's current score to update and check for bust.
			PlayerScore = scoreHand(PlayerHand, PlayerCardCount);
		} while (PlayerHits && PlayerScore < 22);

		// Once the player is done, a check is taken place to see if  busted
		if (PlayerScore > 21) {

			// The Player busted. The House wins.
			scores(users);
			cout << "The House Wins!" << endl;
			cout << "You lost $" << bets << endl;
			displayScoresAndHands(HouseHand, PlayerHand,HouseCardCount, PlayerCardCount);
		}
		else {

			// If the player didn't bust, then the house takes hits below 17
			int HouseScore = scoreHand(HouseHand, HouseCardCount);
			while (HouseScore < 17) {
				HouseHand[HouseCardCount] = nextCard(CardsDealt,NewCard);
				++HouseCardCount;
				HouseScore = scoreHand(HouseHand, HouseCardCount);
			}

			bool HouseBusts = (HouseScore > 21);
			if (HouseBusts) {
				// The House busted. Player wins
				scores(users);
				cout << "You Win!" << endl;
				bets = bets * 2;
				cout << "You gained $" << bets << endl;
				users->score = bets + users->score;
				displayScoresAndHands(HouseHand, PlayerHand,HouseCardCount, PlayerCardCount);
			}
			else {

				// Compare scores and determine the winner
				if (PlayerScore == HouseScore) {

					// Tie. This is called a "push."
					scores(users);
					cout << "Tie!" << endl;
					cout << "You gained $0" << endl;
					users->score = bets + users->score;
					displayScoresAndHands(HouseHand, PlayerHand,HouseCardCount, PlayerCardCount);
				}
				else if (PlayerScore > HouseScore) {

					// The Player wins
					scores(users);
					cout << "You Win!" << endl;
					bets = bets * 2;
					cout << "You gained $" << bets << endl;
					users->score = bets + users->score;
					displayScoresAndHands(HouseHand,PlayerHand,HouseCardCount, PlayerCardCount);
				}
				else {

					// The House wins
					scores(users);
					cout << "The House Wins!" << endl;
					cout << "You lost $" << bets << endl << endl;
					displayScoresAndHands(HouseHand, PlayerHand,HouseCardCount, PlayerCardCount);
				}
			}
		}

		cout << "Would you like to play another game or end? yes(1) or no(2) " << endl;
		cin >> choice;
		while (!((choice == 1) || (choice == 2))) { // Validation if entered wrong choice
			cout << "You entered the wrong choice.\nPlease enter again: ";
			cin >> choice;
		}

		if (choice == 2) {
			flag = false;
                        accountlogin(users, CardsDealt, HouseHand, PlayerHand, HouseCardCount, PlayerCardCount);
		}
		else {
			flag = true;
		}
	}
}

void scores(Player *users)
{
	// Declarations
	fstream inScores;
	string line;
	string userName;
	int score;
	bool found = false;

        // Username & Score Declaration to make it easier
	userName = users->username;
	score = users->score;

	inScores.open("userscore.dat", ios::in | ios::out); // Stores the username and score
		while (getline(inScores, line) && !found) {
			if (line.compare(userName) == 0) { //match username If
				found = true; // If true score added to file
				inScores << score;
			}
		}
	inScores.close();
}

void shuffle(bool CardsDealt[]) {

	for (int Index = 0; Index < 52; ++Index) {
		CardsDealt[Index] = false;
	}
}

void displayCard(int Card) {

    char Ace[] = "Ace";
    char Ten[] = "Ten";
    char Jack[] = "Jack";
    char Queen[] = "Queen";
    char King[] = "King";
    int length;
	// Displays the Rank
	const int Rank = (Card % 13);

	if (Rank == 0) {
            length = strlen(Ace);
            for (int i = 0; i < length; i++)
            {
                cout << Ace[i];
            }
	}
	else if (Rank < 9) {
		cout << (Rank + 1);
	}
	else if (Rank == 9) {
            length = strlen(Ten);
            for (int i = 0; i < length; i++)
            {
                cout << Ten[i];
            }
	}
	else if (Rank == 10) {
            length = strlen(Jack);
            for (int i = 0; i < length; i++)
            {
                cout << Jack[i];
            }
	}
	else if (Rank == 11) {
            length = strlen(Queen);
            for (int i = 0; i < length; i++)
            {
                cout << Queen[i];
            }
	}
	else {
            length = strlen(King);
            for (int i = 0; i < length; i++)
            {
                cout << King[i];
            }
	}

	// Displays the Suit
	const int temp = (Card / 13);
        int const *ptr = &temp;

	if (*ptr == 0) {
		cout << " Of Clubs ||";
	}
	else if (*ptr == 1) {
		cout << " Of Diamonds ||";
	}
	else if (*ptr == 2) {
		cout << " Of Hearts ||";
	}
	else {
		cout << " Of Spades ||";
	}
}

void displayHand(int hand[], const int CardCount) {

	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = hand[CardIndex];
		displayCard(NextCard);
		cout << " ";
	}
	cout << endl;
}

void displayScoresAndHands(int PlayerHand[],int HouseHand[], const int HouseCardCount, const int PlayerCardCount) {

	cout << "House's Hand: Score : " << scoreHand(HouseHand, HouseCardCount) << endl;
	displayHand(HouseHand, HouseCardCount);
	cout << "\nPlayer's Hand Score : " << scoreHand(PlayerHand, PlayerCardCount) << endl;
	displayHand(PlayerHand, PlayerCardCount);
	cout << endl;
}

int nextCard(bool CardsDealt[], int N) {

	bool CardDealt = true;
	do {
		N = (rand() % 52);
		if (!CardsDealt[N]) {
			CardDealt = false;
		}
	} while (CardDealt);
	return N;
}

int scoreHand(int hand[], const int CardCount) {

	int AceCount = 0;
	int Score = 0;
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = hand[CardIndex];
		const int Rank = (NextCard % 13);
		if (Rank == 0) {
			++AceCount;
			++Score;
		}
		else if (Rank < 9) {
			Score = Score + (Rank + 1);
		}
		else {
			Score = Score + 10;
		}
	}
	while (AceCount > 0 && Score < 12) {
		--AceCount;
		Score = Score + 10;
	}
	return Score;
}