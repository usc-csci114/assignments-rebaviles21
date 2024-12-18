#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <cmath>

#include <matplot/matplot.h>

using namespace std;
using namespace matplot;

// set up to parse the data needed 
// 0 , 1, 2, 3, 4
//Student_ID,Study_Hours_Per_Day,Extracurricular_Hours_Per_Day,Sleep_Hours_Per_Day,Social_Hours_Per_Day,Physical_Activity_Hours_Per_Day,GPA,Stress_Level


int main(){
    std::ifstream csv("student_lifestyle_dataset.csv");

    if(csv.fail()) { // error if the file isnt being read
        cout << "File was unable to be open" << endl;
        return 1; 
    }
    string line;
    getline(csv,line); //removes the header
    //vectors needed for linear regression
    vector<double> studyHours;
    vector<double> sleepHours;
    vector<double> exerciseHours; 
    vector<double> gpa;
    vector <int> stress; 
    string parse;
    int dataLine = 0;
    

    // we want to parse (study hours, sleep, and physical activity for linear regression), quantify stress into 3 values (1 to 3) , and gpa are held 

    //1. parse the data into respective vectors
    while(getline(csv,parse)) {
        int header = 0;
        // dataLine++;
        // cout << "line of data on: " << dataLine << endl;
        stringstream ss(parse); //grabs the individual whole line of information
        while(getline(ss,line,',')){
            // cout << "line: " << line << endl;
            // cout << "header: " << header << endl;
            if (header == 1 ){ // this is study hours
                double study = stod(line);
                studyHours.push_back(study);
            }
            else if (header == 3 ) { // sleep hours
                double sleep = stod(line);
                sleepHours.push_back(sleep);
            } 
            else if(header == 5) { // 6th column is physical activity (hours)
                double physical = stod(line);
                exerciseHours.push_back(physical);
            }
            //stress quantitifaction 
            else if(header == 6) { // 7th csv line is gpa
                double gpaVal = stod(line);
                gpa.push_back(gpaVal);
            }
            else if(header == 7) { //stress
                int low = 1;
                int mod = 2;
                int high = 3;
                //need to quantify the points
                //cout << line << endl;

                if (line[0] == 'L') {
                    //cout << "in loop low" << endl;
                    stress.push_back(low);
                }
                if(line[0] == 'M') {
                    //cout << "in loop mod" << endl;
                    stress.push_back(mod);
                }
                if(line[0] == 'H') { // since the data is clean it will only be high
                    //cout << "in loop high" << endl;
                    stress.push_back(high);
                }
            }
            header++; //updates the placement within the line so we can accurately check each line  
        }
    }

    //once the data is parsed into vectors, we can assemble linear regression for study hours, physical activity, and sleep per night with gpa (y)
    //these calculations are only for the line formation so it should only be the independent variables

    double studySum = 0;
    for( int i = 0; i< studyHours.size(); i++) { //study
        studySum += studyHours[i];
    }
    double physicalSum = 0;
    for(int i = 0; i < exerciseHours.size(); i++) {
        physicalSum += exerciseHours[i];
    }

    double sleepSum = 0;
    for(int i = 0; i < sleepHours.size();i++) {
        sleepSum += sleepHours[i];
    }
    double gpaSum = 0;
    for(int  i = 0; i < gpa.size();i++) {
        gpaSum += gpa[i];
    }
    double stressSum = 0;
    for(int i = 0; i < stress.size();i++) {
        stressSum += stress[i];
    }

    ///independent variables means
    double mean_study = studySum/studyHours.size();
    double mean_physical = physicalSum/exerciseHours.size();
    double mean_sleep = sleepSum/sleepHours.size();
    double mean_stress = stressSum/stress.size();
    //dependent variable mean
    double mean_gpa = gpaSum/gpa.size();


    //find the inividual betas (only for the predictors)
    double study_beta = 0.0;
    double physical_beta = 0.0;
    double sleep_beta = 0.0;
    //stress and gpa for this will be predicted (i will be doing stress vs. gpa to see if there is a correlational relationship)
    double stress_beta = 0.0; 


    //uses those values to calculate beta with respect to gpa (dependent)
    double studyNum = 0.0;
    double studyDenom = 0.0;
    double studyNumTwo = 0.0;
    double studyDenomTwo = 0.0;

    double physNum = 0.0;
    double physDenom = 0.0;
    double physNumTwo = 0.0;
    double physDenomTwo = 0.0;

    double sleepNum = 0.0;
    double sleepDenom = 0.0;
    double sleepNumTwo = 0.0;
    double sleepDenomTwo = 0.0;

    double stressNum = 0.0;
    double stressDenom = 0.0;

    // for study hours
    for(int i = 0; i < studyHours.size();i++) {
        studyNum += (studyHours[i] - mean_study)*(gpa[i]-mean_gpa);
        studyDenom += pow((studyHours[i] - mean_study),2);
    }
    //physical
    for(int i = 0; i < exerciseHours.size();i++) {
        physNum += (exerciseHours[i] - mean_physical)*(gpa[i]-mean_gpa);
        physDenom += pow((exerciseHours[i] - mean_physical),2);
    }
    //sleep
    for(int i = 0; i < sleepHours.size();i++) {
        sleepNum += (sleepHours[i] - mean_sleep)*(gpa[i]-mean_gpa);
        sleepDenom += pow((sleepHours[i] - mean_sleep),2);
    }
    //stress
    for(int i = 0; i < stress.size();i++) {
        stressNum += (stress[i] - mean_stress)*(gpa[i]-mean_gpa);
        stressDenom += pow((stress[i] - mean_stress),2);
    }

    //uses those values to calculate beta with respect to STRESS (we want to also accurately predict stress levels)

    //study hours
    for(int i = 0; i < studyHours.size();i++) {
        studyNumTwo += (studyHours[i] - mean_study)*(stress[i]-mean_stress);
        studyDenomTwo += pow((studyHours[i] - mean_study),2);
    }
    //physical
    for(int i = 0; i < exerciseHours.size();i++) {
        physNumTwo += (exerciseHours[i] - mean_physical)*(stress[i]-mean_stress);
        physDenomTwo += pow((exerciseHours[i] - mean_physical),2);
    }
    //sleep
    for(int i = 0; i < sleepHours.size();i++) {
        sleepNumTwo += (sleepHours[i] - mean_sleep)*(stress[i]-mean_stress);
        sleepDenomTwo += pow((sleepHours[i] - mean_sleep),2);
    }


    //calculate beta (for gpa and stress dependent variables) 
    
    //stress and gpa for this will be predicted (i will be doing stress vs. gpa to see if there is a correlational relationship)
    
    //  //wrt to gpa
    // cout << "Below is the beta and alpha values for the predictor variables with respect to GPA: " << endl;
    study_beta = studyNum/studyDenom;
    //cout << "beta for study: " << study_beta << endl;
    physical_beta = physNum/physDenom;
    //cout << "beta for physical: " << physical_beta << endl;
    sleep_beta = sleepNum/sleepDenom;
    //cout << "beta for sleep: " << sleep_beta << endl;
    stress_beta = stressNum/stressDenom;
    // cout << "beta for stress: " << stress_beta << endl;
    // cout << "-------------------------------" << endl;
    // cout << "Alpha values: " << endl;

    //alpha values for gpa
    double alphaStudy = mean_gpa - (study_beta* mean_study);
    //cout << "alpha with study: " << alphaStudy << endl;
    double alphaSleep = mean_gpa - (sleep_beta* mean_sleep);
    //cout << "alpha with sleep: " << alphaSleep << endl;
    double alphaPhysical = mean_gpa - (physical_beta*mean_physical);
    //cout << "alphas with physical activity : " << alphaPhysical << endl;
    double alphaStress = mean_gpa - (stress_beta*mean_stress);
    //cout << "alpha with stress: " << alphaStress << endl;
    //cout << "------------------------------" << endl;


    // wrt to stress
    //cout << " Below is the beta and alpha values for the predictor with respect to stress: " << endl; 
    double study_betaTwo = studyNumTwo/studyDenomTwo;
    //cout << "beta for study: " << study_betaTwo << endl; 
    double physical_betaTwo = physNumTwo/physDenomTwo;
    //cout << "beta for physical: " << physical_betaTwo << endl;
    double sleep_betaTwo = sleepNumTwo/sleepDenomTwo;
    //cout << "beta for sleep: " << sleep_betaTwo << endl;

    //calculate alpha wrt to gpa
    double alphaStudyTwo = mean_stress - (study_betaTwo*mean_study);
    //cout << "alpha for study wit respect to stress: " << alphaStudyTwo << endl;
    double alphaSleepTwo = mean_stress - (sleep_betaTwo * mean_sleep);
    //cout << "alpha for sleep with respect to stress: " << alphaSleepTwo << endl;
    double alphaPhysicalTwo = mean_stress - (physical_betaTwo*mean_physical);
    //cout << "alpha for physical with respect to stress: " << alphaPhysicalTwo << endl;


    //using model find the pnts ( wrt gpa)
    vector <double> fiPointsStudy;
    vector <double> fiPointsPhysical;
    vector <double> fiPointsSleep;
    vector <double> fiPointsStress;

    vector <double> fiPointsStudyStr;
    vector <double> fiPointsPhysicalStr;
    vector <double> fiPointsSleepStr;

    //study hours 
    for(int i = 0 ; i< studyHours.size();i++) {
        double fi = alphaStudy + (study_beta* studyHours[i]);
        fiPointsStudy.push_back(fi);
    }
    //exercise per day (by hour)
    for(int i = 0 ; i < exerciseHours.size();i++) {
        double fi = alphaPhysical + (physical_beta* exerciseHours[i]);
        fiPointsPhysical.push_back(fi);
    }
    //stress
    for(int i = 0 ; i< stress.size();i++) {
        double fi = alphaStress + (stress_beta * stress[i]);
        fiPointsStress.push_back(fi);
    }
    //sleep
    for(int i = 0 ; i< sleepHours.size();i++) {
        double fi = alphaSleep + (sleep_beta* sleepHours[i]);
        fiPointsSleep.push_back(fi);
    }
    //wrt to sleep

    for(int i = 0 ; i< studyHours.size();i++) {
        double fi = alphaStudyTwo + (study_betaTwo* studyHours[i]);
        fiPointsStudyStr.push_back(fi);
    }
    //exercise per day (by hour)
    for(int i = 0 ; i < exerciseHours.size();i++) {
        double fi = alphaPhysicalTwo+ (physical_betaTwo* exerciseHours[i]);
        fiPointsPhysicalStr.push_back(fi);
    }
    for(int i = 0 ; i< sleepHours.size();i++) {
        double fi = alphaSleepTwo + (sleep_betaTwo* sleepHours[i]);
        fiPointsSleepStr.push_back(fi);
    }


    //ss res (wrt to gpa)
    double ssResSleep = 0.0;
    double ssTotSleep = 0.0;
    for(int i = 0; i< fiPointsSleep.size();i++) {
        ssResSleep += pow((gpa[i]-fiPointsSleep[i]),2);
        ssTotSleep += pow((gpa[i]-mean_gpa),2);
    }
    double rSleep = 1-(ssResSleep/ssTotSleep);
    //cout << "r squared sleep : " << rSleep << endl;

    double ssResStudy = 0.0;
    double ssTotStudy = 0.0;
    // cout << "fi point size: " << fiPointsStudy.size() << endl;
    // cout << "gpa size: " << gpa.size() << endl;
    for(int i = 0; i< fiPointsStudy.size();i++) {
        ssResStudy += pow((gpa[i]-fiPointsStudy[i]),2);
        ssTotStudy += pow((gpa[i]-mean_gpa),2);
    }
    // cout << "rRes : " << ssResStudy << endl;
    // cout << "rRes Total: " << ssTotStudy << endl;
    double rStudy = 1 - (ssResStudy/ssTotStudy);
    //cout << "r squared study : " << rStudy << endl;

    double ssResPhys = 0.0;
    double ssTotPhys = 0.0;
    for(int i = 0; i< fiPointsPhysical.size();i++) {
        ssResPhys += pow((gpa[i]-fiPointsPhysical[i]),2);
        ssTotPhys += pow((gpa[i]-mean_gpa),2);
    }
    double rPhys = 1 - (ssResPhys/ssTotPhys);
    //cout << "r squared physical: " << rPhys << endl;
 

    double ssResStress = 0.0;
    double ssTotStress = 0.0;
    for(int i = 0; i< fiPointsStress.size();i++) {
        ssResStress += pow((gpa[i]-fiPointsStress[i]),2);
        ssTotStress += pow((gpa[i]-mean_gpa),2);
    }
    double rStress = 1 - (ssResStress/ssTotStress);
    //cout << "stress (r): " << rStress << endl;

    //ss res (wrt to stress)
    double ssResSleepStr = 0.0;
    double ssTotSleepStr = 0.0;
    for(int i = 0; i< fiPointsSleepStr.size();i++) {
        ssResSleepStr += pow((stress[i]-fiPointsSleepStr[i]),2);
        ssTotSleepStr += pow((stress[i]-mean_stress),2);
    }
    double rSleepStr = 1 - (ssResSleepStr/ssTotSleepStr);
    //cout << "r sleep (stress) : " << rSleepStr << endl;

    double ssResStudyStr = 0.0;
    double ssTotStudyStr = 0.0;
    for(int i = 0; i< fiPointsStudyStr.size();i++) {
        ssResStudyStr += pow((stress[i]-fiPointsStudyStr[i]),2);
        ssTotStudyStr += pow((stress[i]-mean_stress),2);
    }
    double rStudyStr = 1 - (ssResStudyStr/ssTotStudyStr);
    //cout << " r study (stres) : " << rStudyStr << endl;
    

    double ssResPhysStr = 0.0;
    double ssTotPhysStr = 0.0;
    for(int i = 0; i< fiPointsPhysicalStr.size();i++) {
        ssResPhysStr += pow((stress[i]-fiPointsPhysicalStr[i]),2);
        ssTotPhysStr += pow((stress[i]-mean_stress),2);
    }
    double rPhysStr = 1- (ssResPhysStr/ssTotPhysStr);
    //cout << "r physical (stress): " << rPhysStr << endl; 

    //plot linear regression for the gpa based on all the factors
    vector <double> trend_x = linspace(0,13); 
    // // //gpa linear reg lines
    vector<double> trend_study = transform(trend_x,[](auto studyHours){return 1.96 + (studyHours*0.15);}); //study linear reg
    vector<double> trend_sleep = transform(trend_x, [](auto sleepHours){return 3.12 + (sleepHours * -0.0009);}); //sleep linear reg
    vector<double> trend_stress = transform(trend_x,[](auto stress){return 2.58 + (stress* 0.23);}); //stress linear reg
    vector<double> trend_ex = transform(trend_x,[](auto exerciseHours){return 3.29 + (exerciseHours*-0.041);});
    //stress  linear rg lines
    vector<double> trend_studyStr = transform(trend_x,[](auto studyHours){return -0.46 + (studyHours * 0.378);}); //study linear reg
    vector<double> trend_sleepStr = transform(trend_x, [](auto sleepHours){return 3.48 + (sleepHours * -0.15);}); //sleep linear reg
    vector<double> trend_exStr = transform(trend_x,[](auto exerciseHours){return 2.62 + (exerciseHours* -0.06);});


    //make the scatter plots (for gpa only)
    auto fig1 = figure(1);
    auto ax1 = fig1->add_subplot(2,2,1);

    string strStudy = to_string(rStudy);
    ax1->plot(studyHours,gpa,"mo");
    ax1->hold(on);
    ax1->plot(trend_x,trend_study, "b");
    ax1->text(3,4.3, "R^2 value = " + strStudy);
    ax1->text(4.0,3.8, "y = 0.15x + 1.96 ");
    ax1->xlabel("Study Hours Per Day");
    ax1->ylabel("GPA");
    ax1->title("Study Hours vs. GPA");

    //second picture
    auto ax2 = fig1->add_subplot(2,2,2);
    string strSleep = to_string(rSleep);
    ax2->plot(sleepHours,gpa,"bo");
    ax2->hold(on);
    ax2->plot(trend_x, trend_sleep,"b");
    ax2->text(2,4, "R^2 = "+ strSleep);
    ax2-> text(4.0,3.8, "y = -0.0009x + 3.12");
    ax2->xlabel("Sleep Per Night");
    ax2->ylabel("GPA");
    ax2->title("Sleep vs. GPA");

    auto ax3 = fig1->add_subplot(2,2,3);
    string strEx = to_string(rPhys);
    ax3->plot(exerciseHours,gpa,"ro");
    ax3->hold(on);
    ax3->plot(trend_x,trend_ex, "b");
    ax3->text(6, 3.6, "y = 0.23x + 2.58");
    ax3->text( 2, 3, "R^2 = " + strEx);
    ax3->xlabel("Physical Actitivity Done (Hours)");
    ax3->ylabel("GPA");
    ax3->title("Hourly Physical Activity vs GPA");

    auto ax4 = fig1->add_subplot(2,2,4);

    string strStr = to_string(rStress);
    ax4->plot(stress,gpa,"oo");
    ax4->hold(on);
    ax4->plot(trend_x, trend_stress,"b");
    ax4->text(4,4.5, "y = -0.041x + 3.29");
    ax4->text(2,4, "R^2 = "+ strStr);
    ax4->xlabel("Stress (scale of 1-3)");
    ax4->ylabel("GPA");
    ax4->title("Stress vs. GPA");

    // to see the second figure comment these two lines out please!!

    show();
    save("gpaGraphs.png");

    //figure 2 (this must be done after we comment it out)
    auto fig2  = figure(2);
    auto ax5 = fig2->add_subplot(2,2,1);

    string rStuSt = to_string(rStudyStr);
    ax5->plot(studyHours,stress,"mo");
    ax5->hold(on);
    ax5->plot(trend_x,trend_studyStr, "b");
    ax5->text(3,5,"y = 0.378x - 0.46 ");
    ax5->text(2,4, "R^2 = " + rStuSt);
    ax5->xlabel("Study Hours Per Day");
    ax5->ylabel("Stress (1-3)");
    ax5->title("Study Hours vs. Stress");

    auto ax6 = fig2->add_subplot(2,2,2);

    string rSlStu = to_string(rSleepStr);
    ax6->plot(sleepHours,stress,"bo");
    ax6->hold(on);
    ax6->plot(trend_x, trend_sleepStr,"b");
    ax6->text(3,5, "y = -0.15x + 3.48");
    ax6->text(2,4, "R^2 =" + rSlStu);
    ax6->xlabel("Sleep Per Night");
    ax6->ylabel("Stress (1-3)");
    ax6->title("Sleep vs. Stress");

    auto ax7 = fig2 -> add_subplot(2,2,3);
    string rPhST = to_string(rPhysStr);
    ax7->plot(exerciseHours,stress,"ro");
    ax7->hold(on);
    ax7->plot(trend_x,trend_exStr, "b");
    ax7->text(3,5, "y = -0.06x + 2.62");
    ax7->text(2, 4, "R^2 = "+ rPhST);
    ax7->xlabel("Physical Actitivity Done (Hours)");
    ax7->ylabel("Stress (1-3)");
    ax7->title("Hourly Physical Activity vs Stress");

    show();
    save("stressGraphs.png");



return 0;
}  