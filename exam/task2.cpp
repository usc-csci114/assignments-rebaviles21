#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <cmath>
#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

int main(){
    std::ifstream csv("bug-attraction.csv");

    if(csv.fail()) { // error if the file isnt being read
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    string line,num,moon,trash;
    int insectSum = 0;

    getline(csv,line); //removes the header

    //FIND THE INSECT COUNT:
    //make the respective vectors
    vector<double> standardMoonLK;
    vector<double> standardMoonBG;
    vector<int> insectCountLK;
    vector<int> insectCountBG;

    while(getline(csv,line)) {
    //skips 
    int insectSum = 0;
    vector<string>col;
    stringstream ss(line); //grabs the individual line
        while(getline(ss,line,',')){
            col.push_back(line);
        }

        string site = col[2];
        cout << "SITE : " << site << endl; 
        double moonVal = stod(col[4]);
        //cout << "MOON VAL: " << moonVal << endl;

        if(site == "LK" || site == "Stunt") {
            standardMoonLK.push_back(moonVal); // changes and hold it in the LK
            // start the count
            int insectSum = 0; 
            // for(int i = 5; i < 17;i++) {
            //     getline(ss,trash,','); // goes through the irrelevant 
            // }
            for(int i = 17; i < 32;i++) {
                // getline(ss,num, ',');
                insectSum += stoi(col[i]); //grabs the total count
            }
            //once it goes through rows
            insectCountLK.push_back(insectSum);
        }
        if(site == "BG") {
            standardMoonBG.push_back(moonVal); // changes and hold it in the LK
            // start the count
            int insectSum = 0; 
            for(int i = 17; i < 32;i++) {
                insectSum += stoi(col[i]); //grabs the total count
            }
            //once it goes through rows
            insectCountBG.push_back(insectSum);
        }
    }    
    //make linear regression lines
    //first find the mean for the LK and BK insect count

    //LK
    int sum = 0;
    for( int i = 0; i< insectCountLK.size();i++) { //lk site
        sum+= insectCountLK[i];
    }
    int moonSum = 0;
    for(int i = 0; i < standardMoonLK.size(); i++) {
        moonSum += standardMoonLK[i];
    }
    //BG
    int sumTwo = 0;
    for(int i = 0; i < insectCountBG.size();i++) {
        sumTwo += insectCountBG[i];
    }
    int moonSumTwo = 0;
    for(int  i = 0; i < standardMoonBG.size();i++) {
        moonSumTwo += standardMoonBG[i];
    }

    double mean_siteLK = sum/insectCountLK.size();
    double mean_siteBG = sumTwo/insectCountBG.size();

    double moonLKMean = moonSum/standardMoonLK.size();
    double moonBGMean = moonSumTwo/standardMoonBG.size();



    double betaNum = 0.0;
    double betaLKNum = 0.0;

    double betaDenom = 0.0;
    double betaLKDenom = 0.0;

    //uses those values to calculate beta (x)
    for(int i = 0; i < standardMoonBG.size();i++) {
        betaNum += (standardMoonBG[i] - moonBGMean)*(insectCountBG[i]-mean_siteBG);
        betaDenom += pow((standardMoonBG[i] - moonBGMean),2);
    }
    for(int i = 0; i < standardMoonLK.size();i++) {
        betaLKNum += (standardMoonLK[i] - moonLKMean)*(insectCountLK[i]-mean_siteLK);
        betaLKDenom += pow((standardMoonLK[i] - moonLKMean),2);
    }
    //calculate beta 
    double beta = betaNum/betaDenom;
    cout << "beta for BG SITES " << beta << endl;
    
    double betaLK = betaLKNum/betaLKDenom;
    cout << "beta for LK and Stunt Sites" << betaLK << endl;

    //calculate alpha
    double alpha = mean_siteBG - (beta*moonBGMean);
    cout << "alpha for BG site " << alpha << endl;

    double alphaLK = mean_siteLK - (betaLK*moonLKMean);
    cout << "alpha for LK and Stunt Sites" << alphaLK << endl;

    //using model find the pnts
    vector <double> fiPointsLK;
    vector <double> fiPointsBG;

    for(int i = 0 ; i< standardMoonBG.size();i++) {
        double fi = alpha + beta* standardMoonBG[i];
        fiPointsBG.push_back(fi);
    }

    for(int i = 0 ; i < standardMoonLK.size();i++) {
        double fi = alphaLK + betaLK* standardMoonLK[i];
        fiPointsLK.push_back(fi);
    }

    //ss res 
    double ssRes = 0.0;
    double ssTot = 0.0;
    for(int i = 0; i< fiPointsLK.size();i++) {
        ssRes += pow((insectCountLK[i]-fiPointsLK[i]),2);
        ssTot += pow((insectCountLK[i]-mean_siteLK),2);
    }
    double ssResBG = 0.0;
    double ssTotBG = 0.0;
    for(int i = 0; i< fiPointsBG.size();i++) {
        ssResBG += pow((insectCountBG[i]-fiPointsBG[i]),2);
        ssTotBG += pow((insectCountBG[i]-mean_siteBG),2);
    }
    // r-squared value

    double rSquared = 1 - (ssRes/ssTot);
    double rSquaredBG = 1- (ssResBG/ssTotBG);

    cout << "R SQUARED LK " << rSquared << endl;
    cout << "R SQUARED BG " << rSquaredBG << endl;
    //trend lines
    std::vector <double> trend_x = linspace(0,1.0,10);
    std::vector<double> trend_y = transform(trend_x,[](auto standardMoonBG){return 11.4284* standardMoonBG + 52; } );
    std::vector<double> trend_z = transform(trend_x, [](auto standardMoonLK){return 26.6825* standardMoonLK + 63;});

    //make the scatter plots
    auto fig = figure();
    auto ax1 = fig->add_subplot(1,3,1);
    auto ax2 = fig->add_subplot(1,3,2);

    //for the standard moon phase and the insect coung for only BG sites
    ax1->plot(standardMoonBG,insectCountBG,"rx");
    ax1->hold(on);
    ax1->plot(trend_x,trend_y, "b");
    ax1->xlabel("Standardized Moon Phase");
    ax1->ylabel("Urban Site Insect Count");
    ax1->title("Standardized Moon Phase vs. BG Site Total Number of Bugs");

    save("BGlinreg.png");

    ax2->plot(standardMoonLK,insectCountLK,"rx");
    ax2->hold(on);
    ax2->plot(trend_x, trend_z,"b");
    ax2->xlabel("Standardized Moon Phase");
    ax2->ylabel("Rural Site Insect Count");
    ax2->title("Standardized Moon Phase vs. LK and Stunt Sites Total Number of Bugs");

   save("LKlinreg.png");

   show();

return 0;
}
