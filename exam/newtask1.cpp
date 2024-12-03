#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <utility>
#include <map>
#include <cmath>

using namespace std;

int main() {
    // first parse the data that the elements.csv has
	ifstream ifile("bug-attraction.csv"); // parse the data

	if(ifile.fail()) { // error if the file isnt being read
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    
    map< string, map <string, int > > lightMap; // map for the data 
    string line;
    // fill in the light type vector with the 
    string order; // first part of the map
    vector<string> header;
    
    // get the header line first
    getline(ifile,line);
    stringstream ss(line);
    string title;

    for(size_t i = 0; i < 33; i ++) {
        
        for(size_t j = 0; i < 192; j++) {

        }
    }
    // now loaded vector with the titles on there start from 17 to header.size()

    while(getline(ifile,line)) { // goes through every line
        

    }
return 0;
}
