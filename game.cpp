#include<iostream>
#include<ctime> // gives access to time() func
using namespace std;


#define Reset        "\033[0m"
//ANSI color codesto change colors
#define DeepRose     "\033[38;5;168m"   
#define DustyPink    "\033[38;5;175m"
#define SoftPink     "\033[38;5;218m"
#define PeachPink    "\033[38;5;217m"
#define BlushGlow    "\033[38;5;211m"
#define RoseGlow     "\033[38;5;219m"
#define PinkShade    "\033[38;5;174m"

class player {  //creating a player class

private:
    int score;

public:

    player(int s) {  //constructor to initialize

        score = s;
    }

    virtual void chooseMove(string m) = 0;//pure virtual function so the player class is abstract
    virtual string getMove() = 0;

    virtual void updateScore() {  //updates the score
        score++;
    }

    int getScore() { //returns the score
        return score;
    }

    //resets the score to 0 again when the user chooses to play again
    void resetScore() {
        score = 0;
    }

    virtual ~player() {}
};

class humanPlayer : public player {

private:
    string yourMove;

public:

    humanPlayer(int s) :player(s) {}

    void chooseMove(string ym) override {
        yourMove = ym;
    }

    string getMove() {
        return yourMove;
    }

};

class computerPlayer : public player {
    //no choosemove function is being implemented so computer player is an abstract class
public:

    computerPlayer(int s) :player(s) {}
};

class easyComputer : public computerPlayer { //Level 1

private:
    string easyCompChoice;

public:

    easyComputer(int s) :computerPlayer(s) {}

    void chooseMove(string) override {
        easyCompChoice = "Rock";//Computer chooses rock everytime
    }

    string getMove() override {
        return easyCompChoice;
    }
};

class mediumComputer : public computerPlayer {

private:
    string mediumCompChoice;

public:

    mediumComputer(int s) :computerPlayer(s) {} //cons calling parent cons

    void chooseMove(string) override {

        int random = rand() % 3; //generates random no btw 0 and 2
        // assigns values to those numbers
        if (random == 0)
            mediumCompChoice = "Rock";
        else if (random == 1)
            mediumCompChoice = "Paper";
        else
            mediumCompChoice = "Scissors";
    }

    string getMove() override {
        return mediumCompChoice; //returns comp random choice
    }
};

//level 3
class hardComputer : public computerPlayer {

private:
    string hardCompChoice;
    string previousMove;

public:

    //constructor for hardcomputer and base initializer list
    hardComputer(int s) :computerPlayer(s) {
    }

    //overridden func for comp to choose randomly in 1st round
    void chooseMove(string playerMove) override {

        if (previousMove == "") {

            int randomMove = rand() % 3;

            if (randomMove == 0)
                hardCompChoice = "Rock";
            else if (randomMove == 1)
                hardCompChoice = "Paper";
            else
                hardCompChoice = "Scissors";
        }

        // Next moves beat player's previous move
        else if (previousMove == "Rock")
            hardCompChoice = "Paper";

        else if (previousMove == "Paper")
            hardCompChoice = "Scissors";

        else
            hardCompChoice = "Rock";

        previousMove = playerMove;
    }

    string getMove() override {
        return hardCompChoice;
    }
};

class game {

private:
    player* p1; //pointers to player objects
    computerPlayer* p2;
    int rounds;

public:

    game(player* hp, computerPlayer* cp, int r) {
        p1 = hp;
        p2 = cp;
        rounds = r;
    }


    void managingGame() {

        string ym, cm;
        //using for loop so that each level has three rounds
        for (int i = 0; i < rounds; i++) {

            cout << DeepRose << "\n<<<<<<<<<<<<<< ROUND " << i + 1 << " of 3 >>>>>>>>>>>>>>" << Reset << endl;

            cout << SoftPink << "Enter move (Rock / Paper / Scissors): " << Reset;
            cin >> ym;

            if (ym != "Rock" && ym != "Paper" && ym != "Scissors") {
                cout << DustyPink << "Invalid Choice!" << Reset << endl; // displays if user chooses invalid choice
                break;
            }

            p1->chooseMove(ym);//calls the choose move function for human player
            p2->chooseMove(ym);//calls the choose move function for computer
            cm = p2->getMove();//computer move is being stored in cm

            cout << RoseGlow << "Computer Choice: " << cm << Reset << endl;

            if ((ym == "Rock" && cm == "Scissors") ||      //checks if user is beating the computer
                (ym == "Paper" && cm == "Rock") ||
                (ym == "Scissors" && cm == "Paper")) {

                p1->updateScore(); //updating the user score
                cout << BlushGlow << "YOU WON THIS ROUND!" << Reset << endl;
            }

            else if (ym == cm) {       //if both enyter thje same move then its a tie
                cout << PeachPink << "IT'S A TIE!" << Reset << endl;
            }

            else {
                p2->updateScore();  //If computer beats then its score gets updated
                cout << DustyPink << "COMPUTER WON THIS ROUND!" << Reset << endl;
            }

            cout << SoftPink << "Your Score: " << p1->getScore() << Reset << endl;  //displays current scores
            cout << SoftPink << "Computer Score: " << p2->getScore() << Reset << endl;
        }

        //declaring the final winner
        if (p1->getScore() > p2->getScore()) {  //if user score is greater than computer then the user wins
            cout << BlushGlow << "YOU WON THE GAME!" << Reset << endl;
        }

        else if (p1->getScore() < p2->getScore()) {  //otherwise the computer wins
            cout << DustyPink << "COMPUTER WON THE GAME!" << Reset << endl;
        }

        else {
            cout << PeachPink << "GAME TIED!" << Reset << endl;
        }



    }


};

int main() {

    srand(time(0)); // starts generating random numbers

    player* p1 = new humanPlayer(0);   //creating player object
    computerPlayer* p2 = nullptr;   //pointing to nothing for now

    int c;
    string playAgain = "yes";
    cout << DeepRose << "<<<<<<<<<< WELCOME TO THE GAME OF ROCK PAPER SCISSORS >>>>>>>>>>" << Reset;
    cout << DeepRose << "\nLet's Start" << Reset;

    //using while loop so the player can play again

    while (playAgain == "yes" || playAgain == "Yes") {


        cout << SoftPink << "\n1. Easy\n2. Medium\n3. Hard\n" << Reset;
        cout << SoftPink << "Choose Level:" << Reset;

        cin >> c;
        delete p2;
        if (c == 1) p2 = new easyComputer(0);
        else if (c == 2) p2 = new mediumComputer(0); //created comp obj for level 2
        else if (c == 3) p2 = new hardComputer(0);
        else
        {
            cout << DustyPink << "Invalid Choice!" << Reset << endl;
            break;
        }
    
        //calls reset score function for computer player
        p2->resetScore();
        //creating game object and passing the player objects
        game g(p1, p2, 3);

        g.managingGame();   //It is responsible for managing the rounds and the score

        //calls resetScore function for human player
        p1->resetScore();

        cout << RoseGlow << "\nPlay again? (Yes/No): " << Reset;
        cin >> playAgain;
    }
    cout << DeepRose << "THANK YOU FOR PLAYING!" << Reset;
    delete p1; //deleting human object
    delete p2;//deletes last computer object

    return 0;
}