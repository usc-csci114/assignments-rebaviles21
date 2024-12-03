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
	ifstream ifile("bug_attaction.csv"); // parse the data

	if(ifile.fail()) { // error if the file isnt being read
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    map< string, map <string, int >> lightMap; // map for the data 
    vector<string> orderHeader;
    map<string,int> percentageVals; //inner map within the map
   //  // inner map within the map
	string line;
    string known; //lightype
    string number;

    // stringstream header(line);
    // fill in the light type vector with the 
    getline(ifile,line); // remove the header
	stringstream header(line);
    

    while(getline(ifile,line,',')) {
        
        stringstream ss(line); // parse one line and the components within that one line
        getline(ss,known, ','); // saves the lightType
        int totalPerLine = 0;
        
        // first skip these values within the header file
        for(int i = 0; i < 16 ; i++) { //attempt: going to try and total up the values and input them into
            getline(header,known, ',');
        }
        //once we reach the idfferent order we can save these into a vector) 
        while(getline(header,known,',')) {
            orderHeader.push_back(known);
        }
        //make inner map (outer map is done)-- can be 0 because this is the beginning of vector
        for(int i = 0 ; i < orderHeader.size();i++) {
            getline(ss, )
        }







    }  

    // what i was trying to do, make the total and have those be within the key associated with the lightType
    // by having the header file, we could try and parse the individual order names and then have those be associated with the initial mapVector
    // once that we can make_pair and associate for every line that is in the for loop
return 0;
}