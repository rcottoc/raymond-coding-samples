#include <iostream>
#include <vector>
#include <limits.h>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

class card {
    private:
        int value;
        string suit;
    public:
        card(void) {                               // default constructor
            this->value = 0;
            this->suit = "Joker";
        }
        card(int value, string suit) {       // This constructor is the one I intend to use; receive card value and suit for initializing each card in the deck
            this->value = value;
            this->suit = suit;
        }
        ~card(void) {}                          // destructor is just in case I need it later
        void textCard(void) {                  // Text verson of card display, used for initial debugging
            cout << this->value << " of " << this->suit << endl;
        }
        void asciiCard(void) {                // The real enchirito. Likely improvable, but it works! It displays the ascii art card #rendering
            cout << "--------------" << endl;
            if (this->value == 1) {
                cout << "|          A |" << endl;
            }
            else if (this->value == 10) {
                cout << "|         10 |" << endl;
            }
            else if (this->value == 11) {
                cout << "|          J |" << endl;
            }
            else if (this->value == 12) {
                cout << "|          Q |" << endl;
            }
            else if (this->value == 13) {
                cout << "|          K |" << endl;
            }
            else {
                cout << "          " << this->value << " |" << endl;
            }
                cout << "|            |" << endl
                     << "|            |" << endl;
            if (this->suit == "Hearts") {
                cout << "|   Hearts   |" << endl;
            }
            else if (this->suit == "Spades") {
                cout << "|   Spades   |" << endl;
            }
            else if (this->suit == "Diamonds") {
                cout << "|  Diamonds  |" << endl;
            }
            else if (this->suit == "Clubs") {
                cout << "|    Club    |" << endl;          // still debating on Club with 4 spaces on each side or Clubs with 3 spaces before and 4 after.  BUT I intend to replace the words in the ascii with the actual symbols so it may not even matter soon enough
            }
                cout << "|            |" << endl
                     << "|            |" << endl;
            if (this->value == 1) {
                cout << "| A          |" << endl;
            }
            else if (this->value == 10) {
                cout << "| 10         |" << endl;
            }
            else if (this->value == 11) {
                cout << "| J          |" << endl;
            }
            else if (this->value == 12) {
                cout << "| Q          |" << endl;
            }
            else if (this->value == 13) {
                cout << "| K          |" << endl;
            }
            else {
                cout << "| " << this->value << "          |" << endl;
            }
                cout << "--------------" << endl;
        }
        int getCardValue(void) {                        // getter for value
            return this->value;
        }
        string getCardSuit(void) {                      // getter for suit
            return this->suit
        }
};
class deck {                                      // deck class is an object primarily made of a vector of card objects but it defines methods for dealer to interact with vector of cards
    private:
        const int decksize = 52;                                                 // just in case
        const string suits[4] = {"Hearts", "Spades", "Diamonds", "Clubs"};     // All valid suits
        vector<card> cardlist;                                                // vector of card objects (sounds a lot more mysterious than deck of cards)
    public:
        deck(void) {                                  // default constructor "shuffles" all values and suits into deck
            for (int s = 0; s < 4; s++) {            // s is short for suit in this context; 4 suits from 0 through 3
                for (int i = 1; i <= 13; i++) {     // i is short for value in this context; 13 values from A through K
                    cardlist.push_back(card(i, suits[s]));   // card constructor invoked, i is passed to value, suits[s] is passed to suit; push_back() adds card to cardlist
                }
            }
        }
        ~deck(void) { // destructor in case of emergency
        }
        void showDeck(void) {                     // Display all deck contents
            for (card thisone : cardlist) {
                thisone.textCard();          // in text
                thisone.asciiCard();        // in ascii
            }
        }
        unsigned getDeckSize(void) {          // Important method for dealer object to determine if reshuffle necessary
            return this->cardlist.size();
        }
        void deckReshuffle(void) {           // seems like this mmight be a waste of memory or something, but I could not come up with a better solution for now
            cardlist.resize(0);         // reset cardlist vector size to 0;
            if (!cardlist.empty()) {   // ideally this never triggers, but just in case make sure it's empty
                cardlist.pop_back();  // fix it if needed
            }
            for (int s = 0; s < 4; s++) {         // s is short for suit in this context; 4 suits from 0 through 3
                for (int i = 1; i <= 13; i++) {  // i is short for value in this context; 13 values from A through K
                    cardlist.push_back(card(i, suits[s]));   // card constructor invoked, i is passed to value, suits[s] is passed to suit; push_back() adds card to cardlist
                }
            }
        }
        card giveCard(int randomized) {                        // This creates a new card object to store a specific index of the deck, then erases that specific index from the vector and returns the copy to caller
            card transfer = cardlist.at(randomized);          // copy index n
            cardlist.erase(cardlist.begin() + randomized);   // erase index n
            return transfer;                                // return copy
        }
};
class player { // I plan for player to be part of vector<player> table, and for each player to have a wallet, name and a hand of cards vector<card> playerhand
    private:
        string name;
    public:
        int wallet;
        int bet;
        vector<card> playerhand;             // Note: investigate if player hand should be private attrib for safety, but for now this will allow the dealer to interact with the player's hand directly
        player(void) {                      // Default player constructor
            this->wallet = 500;
            this->name = "Gina";
        }
        player(string name) {        // name argument passed
            this->wallet = 500; 
            this->name = name;
        }
        player(string name, int wallet) {
            this->wallet = wallet;
            this->name = name;
        }
        ~player(void) {                // emergency destructor
        }
        void setPlayerName(string name) {
            this->name = name;
        }
        string getPlayerName(void) { 
            return this->name;
        }
/*
        void setPlayerWallet(int wallet) {         // this is for future me, when I finally make wallet private and such
            this->wallet = wallet;
        }
*/
        int getPlayerWallet(void) {
            return this->wallet;
        }
        void showHand(void) {                        // this will allow the player to view their hand #rendering
            for (card each : this->playerhand) {
                each.asciiCard();
                cout << "  ";
            }
            cout << endl;
        }
};
class table {
    public:
        vector<player> players;

        table(void) {
        }
        ~table(void) {
        }
        void drawTable(void) {
            cout << "###########################################################################" << endl
                 << "|                   ___________________________________                   |" << endl
                 << "|                  |                                   |                  |" << endl
                 << "|                  |                                   |                  |" << endl
                 << "|                  |           POCKET CASINO           |                  |" << endl
                 << "|                  |                                   |                  |" << endl
                 << "|                  |                                   |                  |" << endl
                 << "|                  |___________________________________|                  |" << endl
                 << "|                                                                         |" << endl
                 << "|                                                                         |" << endl
                 << "###########################################################################" << endl;
        }
        bool playerJoin(void) {         // players get added to player vector
            if (this->players.size() < 4) {            // max players per table = 4
                cout << "New Player Name: ";
                string name = "";
                ws(cin);
                getline(cin, name);
                player newPlayer(name);
                players.push_back(newPlayer);
                return true;
            }
            return false;
        }
};
class dealer {            // dealer objects will handle all interactions between the players and the deck
    private:
        int pot;
        int wallet;
        vector<card> dealerhand;
    public:
        dealer(void) {
            this->wallet = INT_MAX;          // Infinite money hax for dealer, tax deductible expense
            this->pot = 0;                  // Temporary storage for amounts being bet
        }
/*
        void peekDeck( vector<card> &deckref ) {  // debugging feature, will comment/delete when finished solution
            cout << deckref.at(0).getCardValue() << " " << deckref.at(0).getCardSuit() << endl;
        }
*/
        bool dealCard (deck &deckref, vector<card> &handref, int randomized) {             // pull random card from deck into Player hand, ERASE it from the deck so no dupes
            if (deckref.getDeckSize() > 5) {                                              // This line is intended to check if deck is running out of cards
                handref.push_back(deckref.giveCard(randomized % deckref.getDeckSize())); // randomized large number modulo deck size will only give a random valid index to give (.giveCard() handles the erasure as well as the transfer)
                                                                                        // randomized is srand(time(NULL), giveCard() uses <vector>.erase() to delete the random card we're giving to the hand from the deck
                return true;
            }
            else if (deckref.getDeckSize() <= 5) {
                cout << "Reshuffling deck...\n\n\n";
                deckref.deckReshuffle();
                system("sleep 4");                                                 // ASAP make branch to determine OS and do OS specific sleep/timeout /t ! OR learn to do this within C++
                handref.push_back(deckref.giveCard(randomized % deckref.getDeckSize()));
                return true;
            }
            return false;
        }
        bool dealDealer(deck &deckref, int randomized) { 
            if (deckref.getDeckSize() > 1) {                                                             // No dealing from empty deck in this casino
                this->dealerhand.push_back(deckref.giveCard(randomized % deckref.getDeckSize()));       // get card, erase card
                return true;
            }
            else if (deckref.getDeckSize() <= 0) {                                                    // I don't know how I could possibly get deck size < 0 but just in case
                cout << "Reshuffling deck...\n\n\n";
                deckref.deckReshuffle();
                system("sleep 4");                                                 // ASAP make branch to determine OS and do OS specific sleep/timeout /t ! OR learn to do this within C++
                this->dealerhand.push_back(deckref.giveCard(randomized % deckref.getDeckSize()));
                return true;
            }
            return false;
        }
        bool takeBet (player &gambler, int amount) {                   // &gambler is the player placing bet, amount is the bet amount
                if (gambler.wallet >= amount) {                       // player objects have wallet for total amount
                    gambler.bet = amount;                            // they also have bet amount to hold how much they currently placed in pot, this will be helpful in aiding the dealer hand out individual winnings
                    gambler.wallet -= amount;                       // wallet must lose bet amount
                    this->pot += amount;                           // pot increased by amount placed
                    return true;                                  
                }
                else {
                    cerr << gambler.getPlayerName() << " cannot make that bet. " << endl
                         << gambler.getPlayerName() << " Wallet: " << gambler.getPlayerWallet() << endl;
                    return false;
                }
        }
        void renderDealer(void) {                                         // Chaddeus Maximus III
            cout << "                                 __________"     << endl
                 << "                               /            \\"  << endl
                 << "                              |    $    $    |"  << endl
                 << "                               \\     ___     /" << endl
                 << "                                \\_____#_____/"  << endl
                 << "                              ______|   |______" << endl
                 << "                            /                   \\" << endl
                 << "                           /   /|            |\\  \\" << endl;
        }
        void showHand(void) {
            for (card each : this->dealerhand) {
                each.asciiCard();
                cout << "   ";
            }
            cout << endl;                               // this line might need removed, I think it's causing unintended newlines
        }
        void countHand(void) {                             // this will let the dealer know whether he should hit or stand
            int counter = 0;
            for (card ace : this->dealerhand) {
                counter += ace.getCardValue();
            }
            return counter;
        }
};

/************************************************/
void banner(void) {
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl
         << "|                             POCKET   CASINO                             |" << endl
         << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void endScene(void) {
    string userChoice = "";
    cout << "Press Return to continue." << endl;
    getline(cin, userChoice);
    system("clear");
}

void startScene(void) {
    system("clear");
    banner();
}

void resetScene(dealer &deal, table &blackjack) {
    startScene();
    deal.renderDealer();
    blackjack.drawTable();
}

int main(void) {
    // player samplePlayer;   // debugging player.
    // vector<player> table; // debugging table.
    deck standard;
    dealer slickhand;
    table blackjack;

    string userChoice = "";
    while(true) {
        srand(time(NULL));
        int randomizer = random();
        startScene();
        cout << "Main Menu: " << endl
             << "\t1) Play Blackjack" << endl
             << "\t2) Watch ad for cash" << endl
             << "\t0) Leave Casino" << endl
             << ">>> ";
        ws(cin);
        getline(cin, userChoice);
/*         if (userChoice == "y") {             // sample outputs
                slickhand.dealCard(standard, samplePlayer.playerhand, randomizer);

                cout << samplePlayer.playerhand.at(0).getCardValue() << " " << samplePlayer.playerhand.at(0).getCardSuit() << endl;

                samplePlayer.playerhand.at(0).asciiCard();

                cout << "Cards left in deck: " << standard.getDeckSize() << endl;

                samplePlayer.playerhand.pop_back();

                endScene();
            }
*/
        if (userChoice == "1") {
            while(true) {
                startScene();
                cout << "1) Manage Players" << endl        // To do: Fix this branch to allow adding or removing players from table. Branch exists, but no removal there just placeholder text
                     << "2) Play Round" << endl
                     << "0) Leave Table" << endl;
                slickhand.renderDealer();
                blackjack.drawTable();
                cout << "What would you like to do?" << endl
                     << ">>> ";
                ws(cin);
                getline(cin, userChoice);
                if (userChoice == "1") {
                    resetScene(slickhand, blackjack);     // NTS: These arguments seem arbitrary, consider rewrite.
                    cout << "What would you like to do?" << endl
                         << "\t1) Add New Player" << endl
                         << "\t2) Remove Player" << endl
                         << "\t0) Back" << endl
                         << "\t>>> ";
                    ws(cin);
                    getline(cin, userChoice);
                    if (userChoice == "1") {
                        if (blackjack.playerJoin()) {
                            cout << "Welcome Players! " << endl;
                            int count = 1;
                            for (player gambler : blackjack.players) {
                                cout << "\tPlayer " << count++ << ": " << gambler.getPlayerName() << endl;
                            }
                        }
                        else {
                            cerr << "Table is full. Player cannot join until another player leaves. " << endl;
                        }
                    }
                    else if (userChoice == "2") {
                        cout << "Placeholder Text for REMOVAL: waste managed" << endl;
                    }
                    else if (userChoice == "0") {
                        continue;
                    }
                    else{
                        cerr << "Invalid selection [ " << userChoice << " ]" << endl;
                    }

                }
                else if (userChoice == "2") {
                    if (standard.getDeckSize() <= 17) {
                        standard.deckReshuffle();
                    }
                    if (blackjack.players.size() >= 1) {
                        for (player gambler : blackjack.players) {
                            bool validAmount = false;
                            while (!validAmount) {
                                cout << "How much would " << gambler.getPlayerName() << " like to bet: ";
                                int money = 0;
                                cin >> money;
                                if (slickhand.takeBet(gambler, money)) {
                                    cout << "Bet received!" << endl;
                                    validAmount = true;
                                }
                            }
                            if (slickhand.dealCard(standard, gambler.playerhand, randomizer)) {
                                cout << gambler.getPlayerName() << " was dealt a card!\n";
                            }
                            else {
                                cerr << "Something went wrong." << endl;
                            }
                        }
                        if (slickhand.dealDealer(standard, randomizer)) {
                            cout << "Dealer was dealt a card!" << endl;
                        }
                        else {
                            cerr << "Something went wrong." << endl;
                        }
                        endScene();
                        for (player gambler : blackjack.players) {
                            bool hitting = true;
                            while (hitting) {
                                resetScene(slickhand, blackjack);
                                cout << "Dealer Hand: " << endl;
                                slickhand.showHand();

                                cout << "Dealer will draw until 16, and stand at 17.\n\nWhat would you like to do?\n\t1) Hit\n\t2) Stand" << endl;
                                cout << ">>> ";
                                ws(cin);
                                getline(cin, userChoice);

                                if (userChoice == "1") {
                                    if (slickhand.dealCard(standard, gambler.playerhand, randomizer)) { // STILL NEEDS A WAY TO CHECK FOR PLAYER BUST
                                        cout << gambler.getPlayerName() << " was dealt a card!" << endl;
                                        system("sleep 2");
                                    }
                                    else {
                                        cerr << "Something went wrong." << endl;
                                        system("sleep 2");
                                    }
                                }
                                else if (userChoice == "2") {
                                    cout << "You chose stand." << endl;
                                    hitting = false;
                                    system("sleep 2");
                                }
                                else {
                                    cerr << "Invalid selection [ " << userChoice << " ]" << endl;
                                }
                                endScene();
                            }
                        }
                        while (slickhand.countHand() <= 16) { 
                            slickhand.dealDealer(standard, randomizer);
                        }

                        /* MAKE LOGIC FOR PLAYERS BEAT DEALER */
                    }
                    else {
                        cerr << "Table is empty! Player(s) must join table to play a round of blackjack." << endl;
                    }
                }
                endScene();
            }
        }
        else if (userChoice == "2") {
            cout << "Choice 2" << endl;  // This needs to be replaced with the instructions for choice 2
            endScene();
        }
        else if (userChoice == "0") {
            cout << "See you next time!" << endl;
            break;
        }
        else {
            cerr << "Invalid selection [ " << userChoice << " ]. Expected 1, 2, or 0. Please try again!.\n Press return to continue." << endl;
            ws(cin);
            getline(cin,userChoice);
            system("clear");
        }
        // blackjack.showDeck();
    }
    return 21;
}
