#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <utility>
#include <map>
#include <stdexcept>
#include<iomanip>
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
    //first string is the order , map <string light type, value > > 
    vector<string> order; // for the order
    vector<string>lightTypesVec; 
    map<string,int> orderVals; //inner map within the map
   //  // inner map within the map
	string line;
    string lightTypes;
    string orderLine;
    string trash;
    string lightLine; 
    int speciesCnt = 0;
    int cnt = 0;

    // remove the header
    //parse each row and grabs the orderHeader types from the header and pushed into vector of str
    getline(ifile,line); 
    stringstream ss(line);
    //
    for(int i =  0; i < 16; i++){
        getline(ss,trash,',');
    }
     for(int i = 17; i < 32; i++) {
        getline(ss,lightLine, ',');
        order.push_back(lightLine); // all the orders
    }
    //loop through data[order[i]] == orderVals;
    for(int i = 0; i < order.size(); i++) {
        orderVals[order[i]] = cnt++; //map with the string that equals the value
    }

    //1. GET LIGHTYPE KEY DONE
    while(getline(ifile,line)) {
        stringstream ss(line); //parses the row
        getline(ss,lightTypes, ','); /// this grabs and stores within the string
        //cout << "Light Types: " << lightTypes << endl;
        lightTypesVec.push_back(lightTypes);
        // if(lightTypesVec.size() <= 15) { // only keeps grabbing the linne until it reaches 15 (all the needed light Types) 
        //     cout << "Light Types" << lightTypes << endl;
        //     lightTypesVec.push_back(lightTypes);
        // }

        for(int i = 0; i < 17;i++) {
            getline(ss,trash, ',');
        }
        for(int i = 17; i < 32; i++) { //grabs from the stringstream
            getline(ss, orderLine, ','); //
                speciesCnt = stoi(orderLine);
                lightMap[lightTypes][order[i-17]] += speciesCnt; // (light type, cnt)

            }
        }

    
    string lightTypeKey;
    string orderKey;
    int orderCount = 0;
    // // to print out (iterator)
    // //sort out the maximum values
    // //sort(lightMap.begin(), lightMap.end());
    int max = 0;
    string maxKey, maxOrder;
    auto it = lightMap.begin();
    while(it != lightMap.end()) {
        lightTypeKey = it->first;
        auto orderKey = it-> second.begin();
        while(orderKey != it->second.end()) {
            orderCount = orderKey->second;
            if(orderCount > max) {
                max = orderCount;
                maxKey = lightTypeKey;
                maxOrder = orderKey->first;
            }
            cout << "Species Order: "<<orderKey->first << endl;
            cout << "Light Type: " << lightTypeKey<< endl;
            cout << "Count: " << orderCount << endl;
            cout<< "---------------------------------" << endl;
            orderKey++;
        }
        it++;
    }
    cout << "MAX Species Order: "<< maxOrder << endl;
    cout << "MAX Light Type: " << maxKey << endl;
    cout << "MAX Count: " << max << endl;
    cout<< "---------------------------------" << endl;

return 0; 
}



    // getline(header,name,',')
    

    // while(getline(ifile,line,',')) {
        
    //     stringstream ss(line); // parse one line and the components within that one line
    //     getline(ss,known, ','); // saves the lightType
    //     int totalPerLine = 0;
        
    //     // first make the total number value
    //     for(int i = 0; i < 16 ; i++) { //attempt: going to try and total up the values and input them into
    //         getline(header,known, ',');
    //     }
    //     // 
    //     while(getline(header,known,',')) { //prediction: facilitates the lightType data 
    //         orderHeader.push_back(known);
    //     }
    //     //make inner map (outer map is done)
    //     for(int i = 16; i < orderHeader.size();i++) {
    //         getline(ss,number,',');
    //         speciesCnt = stoi(number); // values in the csv are strings-> int
    //         //associate the map with the speciesCnt
    //         int denom = orderHeader.size();
    //         int percent = (speciesCnt/denom)*100;
    //         percentageVals[orderHeader[i]] = percent; //inner map within the map
    //         // by having the key (the string values be equal to the speciesCnt the percentages will remain the same
    //     }

    //     cout<< "Light Type" << setw(8) << "Species Name" << setw(8) << "maxPercent" << endl;
    //     cout << string(24,'-') << endl;
         
         






    //}  
// return 0; 
// }