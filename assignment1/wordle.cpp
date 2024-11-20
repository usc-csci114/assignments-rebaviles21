#include<iostream>
#include<vector>
#include <fstream>
#include <string>
#include <sstream>




using namespace std;

//Function Protypes
string green = "\033[92m";
string yellow = "\033[93m";
string off = "\033[0m";

void makeBoard(vector <string> guess);
string matchLettersinWrongPlace(string &userInput, string &wordInGame);
bool doesLetterAppear(string &userInput, string &wordInGame);


int main() {
    vector<string>board(6);
    vector<string> words;
    vector<string> guess;
    vector<string> guessTry; 
    ifstream ifile("wordlist.txt");

    if(ifile.fail()) {
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    string input; // add all the words into this stream
    while(ifile >> input) {
        words.push_back(input);
    }

// start off the game: (sets up the blank board)

    string userInput;
    srand(time(0));
    string wordInGame = words[rand()%words.size()];
    cout << wordInGame << endl;
    makeBoard(guess);

    cin >> userInput;  // guess the user selects 

    //actual game (enters the loop)
    while(userInput != "quit" || userInput == "new") { // the whole game will play out
        if(userInput == "new") {
            guess.clear();
            wordInGame = words[rand()%words.size()];
            cout<< wordInGame << endl;
            makeBoard(guess);
            cin >> userInput;
        }
        if(userInput == "quit") {
            break;
        }
        if(guess.size() == 6) { // if the 
            cout << "The correct word is " << wordInGame<< endl;
            cout << "Do you want to play again?? Quit for no. New for Yes!" << endl;
            break; // leave the while loop 
        }
        if((userInput.size() < 5 || userInput.size() > 5)) { // must be 5 letters to be considered valid in order to play the game
            cout << "Invalid guess. Please choose another one" << endl;
            cin >> userInput;
        }    
        string word = matchLettersinWrongPlace(userInput, wordInGame);
        guess.push_back(word);
        // done to print the board every single time something is pushed back into the vector
        makeBoard(guess);

        if(userInput == wordInGame) {
            cout <<"You guessed the correct word! Good job. Would you like to play again? quit for no ; new for yes" << endl;
        }

        cin >> userInput;
}
    cout << "Thanks for playing" << endl;    

    
  ifile.close();
  return 0;   
}

void makeBoard(vector<string>guess) {
    vector<string>board(6, "*****");
    for(int i =0 ; i < guess.size(); i++ ) {
        board[i] = guess[i];
    }
    for(int i = 0; i < 6; i++) {
        cout << board[i] << endl;
    }
}    

// string matchLettersinWrongPlace(string &userInput, string &wordInGame) {
//         bool match[wordInGame.size()];
//         for(int i = 0 ; i < wordInGame.size(); i++) {
//             match[i] = false;
//         }
//     stringstream ss;
//         // right place?
//        for(int i = 0 ; i < wordInGame.size();i++) {
//             if(userInput[i] == wordInGame[i]) { //matches at that correct placement (if all right should match all the way)
//             ss << green << userInput[i] << off;
//             match[i] = true;
//             }
//        }    
//         //is it in the word? if it is but wrong spot
//         bool wordExists = false;
//         for(int i = 0 ; i < wordInGame.size(); i++ ){
//             if(!match[i]) {
//                 // bool wordExists = false;
//                 for(int j = 0; j < wordInGame.size(); j++) {
//                     wordExists = false;
//                     if(userInput[i] == wordInGame[j] && !match[j]) {
//                         //cout << "j: " << i << "userInput[j]: " << userInput[j] << endl;
//                         ss << yellow << userInput[i] << off;
//                         match[j] = true;
//                         wordExists = true;
//                         break;
//                     }
//                 }
//                 if(!wordExists) {
//                   ss << off << userInput[i];   
//                 }  
//             }
//         }
//     return ss.str();    
    
// }  


//debugging concerns word is repeated at the end

//user input is being colored yellow even though its not in the word
// incorrect yellow words (some of them are off) 

//REASON is that they use time letter which is just show amount of times code appears 
// the reduction in the time letters appears to not be working...

string matchLettersinWrongPlace(string &userInput, string &wordInGame) {
    stringstream ss;
        // right place?
    for(int i = 0 ; i < wordInGame.size();i++) {
                // spot in the word
        bool wordExists = false; 
        bool matched = false;
        if(userInput[i] == wordInGame[i]) { //matches at that correct placement (if all right should match all the way)
            ss << green << userInput[i] << off;
            wordExists = true;
            matched = true; // if there is a matched color cannot be changes
        }    
            // they dont have the same spot but 
        else {
            for(int j = 0; j < wordInGame.size(); j++) { //loop checks if the word is in the user
                if(userInput[i] == wordInGame[j] && matched == false) { // i because you want to compare the whole guess[i] to the wordingame
                    ss << yellow << userInput[i] << off;
                    wordExists = true;
                    matched = true;
                    break; // there is a good match!
                }
            }
            if(!wordExists && !matched) {
                ss << off << userInput[i]; 
            }
        }
    }
    bool alphabet[26];
    for(int i = 0 ; i < 25; i++) {
        alphabet[i] = false;
    }
    return ss.str();    
    
}