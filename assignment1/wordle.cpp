#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

main(int argc, char* argv[]) {
    vector<string> words;

    ifstream ifile("wordlist.txt");

    if(ifile.fail()) {
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    string input;
    while(ifile >> input) {
        words.push_back(input);
    }

    // once everything is put into the file; lets play the game wordle

    
    ifile.close();
  return 0;   
}

