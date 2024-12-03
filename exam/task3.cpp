//#### Task 3: Bar Chart

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
#include <matplot/matplot.h>

using namespace matplot;
using namespace std;
//protoype for sort;
struct compclass {
  bool operator() ( pair<string, int>& a, pair<string, int>& b) { return (a.second > b.second);}
} comp;

int main() {
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
    vector<int> topCnt;
    // inner map within the map
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
    vector<vector<int>> barData;
    vector<int> barCount;
    vector <string> orderNames; 
    //1. GET LIGHTYPE KEY DONE
    while(getline(ifile,line)) {
        stringstream ss(line); //parses the row
        getline(ss,lightTypes, ','); /// this grabs and stores within the string
        //cout << "Light Types going in Vector" << lightTypes << endl;
        lightTypesVec.push_back(lightTypes);
        // if(lightTypesVec.size() <= 6) { // only keeps grabbing the linne until it reaches 15 (all the needed light Types) 
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
    vector <string> ltPlot;
    

    auto it = lightMap.begin();
    while(it != lightMap.end()) {
        lightTypeKey = it->first;
        auto orderKey = it-> second.begin();
        map<string,int>& orderVals = it->second;
        cout << "Light Type: WIthin test  " << lightTypeKey << endl; //test code (getting killed???)
        
        vector<pair<string,int >> sortedOrders;
        for(const auto& orderKey: orderVals) {
            //cout << "Sorted Order " << orderKey  << endl;
            sortedOrders.push_back(orderKey); // we can "convert" the map to be a vector
        }
        // for(size_t i = 0; i < sortedOrders.size();i++) {
        //     for(size_t j = i+1; j < sortedOrders.size();j++) {
        //         if(sortedOrders[j].second > sortedOrders[i].second) { //comparing values
        //             swap(sortedOrders[i],sortedOrders[j]);
        //         }
        //     }
        // }
        int topFour = 0; 
        std::sort(sortedOrders.begin(),sortedOrders.end(), comp);
    
        vector <int > barCount;
        vector<string> orderNames;

        //printing it out (just to see if it did it right)
        auto orderIt = sortedOrders.begin();
        //int topFour = 0;
        while(orderIt!= sortedOrders.end() && topFour < 4) {
            barCount.push_back(orderIt->second);
            orderNames.push_back(orderIt->first);

            cout<< "Order:" << orderIt->first << endl;; // should be fine??
            cout<< "Count:" << orderIt->second << endl;
            orderIt++;
            topFour++;
        }

        barData.push_back(barCount); // should be parsing

        it++;
        cout << "------------------------" << endl;
    //     for (size_t i = 0; i < barData.size(); ++i) {
    
   for (size_t i = 0; i < barData.size(); ++i) {
    for (size_t j = 0; j < barData[i].size(); ++j) {
        cout << "Bar Data [" << i << "][" << j << "]: " << barData[i][j] << endl;
    }
}
    }
    //Group Bar Graph (try one)


    //vector<vector<int>> trialData = {{1262,235,101,77},{813,148,56,50},{799,193,74,55}, {1599,337,234,83}, {943,198,127,62},{163,99,50,15}};
    // bar(trialData);
    // bar(trialData[0]);
    // gca()->x_axis().ticklabels({"A"});

    bar(barData); // y is the counts of the order
    xlabel("Light Types");
    ylabel("Insect Count within these Orders");
    title("Light Types and Top 4 Orders");
    gca()->x_axis().ticklabels({"A","B","C","CFL","LED","NO"});
    plt::legend();

    // // // need to label for lightTypes and restrict for only 4

    show(); save("groupBarPlot.png");


return 0;
}      
    