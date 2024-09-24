#include <iostream>
#include <fstream>
#include <iomanip>
#include <string> 
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

//FUNCTION PROTOTYPES:

double max(vector<double> vec, int startVal, double value);
double min(vector<double> data, int startVal, double value);
double printAvg(vector<double> data, double sum, int startVal);
double printStdev(vector<double> data, double mean, int startVal);

int main() {
    // read the file and make vectors to store all the values(variables needed within the code)
   vector<double> sepalLength;
   vector<double> sepalWidth;
   vector<double> petalLength;
   vector<double> petalWidth;
   double sLength;
   double sWidth;
   double pLength;
   double pWidth;
  string species;


    string iris; 
    ifstream ifile("iris.txt");

    // ensures the file has been open correctly
    if(ifile.fail()) {
        cout << "File was unable to be open" << endl;
        return 1; 
    }

    //EDIT: getline 
    //once the data is able to be read properly

    //stod is not converting properly (throwing an exception)
    string line;
    while(getline(ifile,iris)) { //grab all 150 lines
        stringstream ss(iris); // grabs one line and parses the data
        getline(ss, line, ','); //grabs the line 
        //cout << line <<  endl;
        sepalLength.push_back(stod(line));  // this is not converting 
        getline(ss, line,',');  
        sepalWidth.push_back(stod(line));
        getline(ss, line,','); 
        petalLength.push_back(stod(line)); 
        getline(ss, line,','); 
        petalWidth.push_back(stod(line));
        getline(ss, line,',');
        getline(ss,line); //adds this in
//unable to do a delimiter while loop instead manually do it for each text line and pushback into the vectors
    }       
    //using this information -- "5.1,3.5,1.4,0.2,Iris-setosa" this is one string
    // must parse into different pieces to analyze the numbers (currently in string form)

    // //now in respective vectors, the doubles 
        double sum1 = 0.0;
        double sum2 = 0.0;
        double sum3 = 0.0;
        double sum4 = 0.0;
// data analysis

    //mean values (Seratosa)
    double seratosaSLengthAvg = printAvg(sepalLength,sum1,0);
    double seratosaSWidthAvg = printAvg(sepalWidth,sum2,0);
    double seratosaPLenthAvg = printAvg(petalLength,sum3, 0);
    double seratosaPWidthAvg = printAvg (petalWidth,sum4,0);
    //mean values(Versicolor)
    double versicolorSLengthAvg = printAvg (sepalLength,sum1,50);
    double versicolorSWidthAvg = printAvg(sepalWidth,sum2,50);
    double versicolorPLengthAvg = printAvg(petalLength,sum3,50);
    double versicolorPWidthAvg = printAvg(petalWidth,sum4,50);
    //mean values(Virginica)
    double virginicaSLengthAvg = printAvg(sepalLength,sum1,100);
    double virginicaSWidthAvg = printAvg(sepalWidth,sum2,100);
    double virginicaPLengthAvg = printAvg(petalLength,sum3,100);
    double virginicaPWidthAvg = printAvg(petalWidth,sum4,100);

    //max values
    double val = 0.0;

    double maxseraSLength = max(sepalLength, 0, val);
    double maxseraSWidth = max(sepalWidth,0,val);
    double maxseraPLength = max(petalLength, 0 , val);
    double maxseraPWidth = max(petalWidth, 0 , val);

    double maxsversiSLength = max(sepalLength, 50, val);
    double maxversiSWidth = max(sepalWidth,50,val);
    double maxversiPLength = max(petalLength, 50, val);
    double maxversiPWidth = max(petalWidth,50, val);

    double maxsvirgSLength = max(sepalLength, 100, val);
    double maxvirgSWidth = max(sepalWidth,100,val);
    double maxvirgPLength = max(petalLength, 100, val);
    double maxvirgPWidth = max(petalWidth,100, val);

    //min values
    double minseraSLength = min(sepalLength, 0, val);
    double minseraSWidth = min(sepalWidth,0,val);
    double minseraPLength = min(petalLength, 0 , val);
    double minseraPWidth = min(petalWidth, 0 , val);

    double minsversiSLength = min(sepalLength, 50, val);
    double minversiSWidth = min(sepalWidth,50,val);
    double minversiPLength = min(petalLength, 50, val);
    double minversiPWidth = min(petalWidth,50, val);

    double minsvirgSLength = min(sepalLength, 100, val);
    double minvirgSWidth = min(sepalWidth,100,val);
    double minvirgPLength = min(petalLength, 100, val);
    double minvirgPWidth = min(petalWidth,100, val);

    //stdev
    
    double stdseraSLength = printStdev(sepalLength, seratosaSLengthAvg, 0);
    double stdseraSWidth = printStdev(sepalWidth, seratosaSWidthAvg, 0);
    double stdseraPLength = printStdev(petalLength, seratosaPLenthAvg, 0);
    double stdserraPWidth = printStdev(petalWidth, seratosaPWidthAvg, 0);

    double stdversiSLength = printStdev(sepalLength, versicolorSLengthAvg, 50);
    double stdversiSWidth = printStdev(sepalWidth, versicolorSWidthAvg, 50);
    double stdversiPLength = printStdev(petalLength, versicolorPLengthAvg, 50);
    double stdversiPWidth = printStdev(petalWidth, versicolorPWidthAvg, 50);

    double stdvirgSLength = printStdev(sepalLength, virginicaSLengthAvg, 100);
    double stdvirgiSWidth = printStdev(sepalWidth, virginicaSWidthAvg, 100);
    double stdvirgiPLength = printStdev(petalLength, virginicaPLengthAvg, 100);
    double stdvirgiPWidth = printStdev(petalWidth, virginicaPWidthAvg, 100);


// table formatting

cout << "								       Iris Data" << endl;
cout<< "-----------------------------------------------------------------------------------------------------" << endl;
cout<< "|            | sepal length       | sepal width        | petal length        | petal width          |" << endl;
cout<< "-----------------------------------------------------------------------------------------------------" << endl;
cout<< "|   setosa   | "<< setprecision(2) <<minseraSLength<< ", "<<maxseraSLength<<", "<<seratosaSLengthAvg<<", " << stdseraSLength << " | ";
cout << setprecision(2) << minseraSWidth << ", "<< maxseraSWidth <<", " << seratosaSWidthAvg << ", " << stdseraSWidth << ", | ";
cout << setprecision(2) << minseraPLength<< ", " << maxseraPLength << ", " << seratosaPLenthAvg << ", " << stdseraPLength << ", | ";
cout << setprecision(2) << minseraPWidth << ", " << maxseraPWidth << ", " << seratosaPWidthAvg<< ", " << stdserraPWidth << ", |" << endl;
cout<< "-----------------------------------------------------------------------------------------------------" << endl;
cout<< "| versicolor | "<< setprecision(2) <<minsversiSLength<< ", "<<maxsversiSLength<<", "<<versicolorSLengthAvg<<", " << stdversiSLength << " | ";
cout << setprecision(2) << minversiSWidth << ", "<< maxversiSWidth <<", " << versicolorSWidthAvg << ", " << stdversiSWidth << ", | ";
cout << setprecision(2) << minversiPLength<< ", " << maxversiPLength << ", " << versicolorPLengthAvg << ", " << stdversiPLength << ", | ";
cout << setprecision(2) << minversiPWidth << ", " << maxversiPWidth << ", " << versicolorPWidthAvg<< ", " << stdversiPWidth << ", |" << endl;
cout<< "-----------------------------------------------------------------------------------------------------" << endl;
cout<< "| virginica  | "<< setprecision(2) <<minsvirgSLength<< ", "<<maxsvirgSLength<<", "<<virginicaSLengthAvg<<", " << stdvirgSLength << " | ";
cout << setprecision(2) << minvirgSWidth << ", "<< maxvirgSWidth <<", " << virginicaSWidthAvg << ", " << stdvirgiSWidth << ", | ";
cout << setprecision(2) << minvirgPLength<< ", " << maxvirgPLength << ", " << virginicaPLengthAvg << ", " << stdvirgiPLength << ", | ";
cout << setprecision(2) << minvirgPWidth << ", " << maxvirgPWidth << ", " << virginicaPWidthAvg<< ", " << stdvirgiPWidth << ", |" << endl;
cout<< "-----------------------------------------------------------------------------------------------------" << endl;


    ifile.close();
return 0;    
}

//to make code more efficinet make functions for all the data analysis (this way we can isolate for only species)

//find the max value
double max(vector<double> vec, int startVal, double value) {
    value = 0.0;
    for(int i  = startVal; i < startVal+50; i ++) {
        if(vec[i] > value) {
            value = vec[i];
        }
    }
    return value;
}

//finds the minimum value
double min(vector<double> data, int startVal, double value) {
    value = 20.0; //reason its 0 is because nothing is less than 0
    for(int i = startVal; i < startVal+50; i ++) {
        if(data[i] < value) {
            value = data[i];
        }
    }
    return value;
}

double printAvg(vector<double> data, double sum, int startVal) {
    sum = 0.0;
    for(size_t i = startVal; i < startVal+50; i++) {
        sum += data[i];
    }
    double average = sum/50;
    return average;
}
// sqrt((xi - mean)^2 / n-1)
//variance is needed per data point
//should the vatiance be added all together?

double printStdev(vector<double> data, double mean, int startVal) {
    double var = 0.0;
    for(size_t i = startVal; i < startVal+50; i++) {
        var += pow((data[i]-mean),2); // does that first point -- should add everything
    }
    //once we have variance (sum of all the values
    //generalize: groups of 50 (n-number of observation)

    double stdev = sqrt(var/49);

    return stdev;
}



//overall technique is fine
//getline for species ( 2D vectors: first dimesnion (species each one))
// member functions 
//seg faukt the vector size was 0 (improper adding of the line to the vector)
//additional errors: delimiter must manually fix it, so the push_back will do proper function using another line then converting it
// change the indices into startVal+ 50 (this is done to )