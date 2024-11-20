#include <iostream>
#include <sstream>
#include <vector>
#include "system.h"

using namespace std;

int main(int argc, char* argv[])
{
    int n;
    int m;
    double input;
    vector<vector<double>> matrix;

    cout << "Input the n and m variables:" << endl;
    cin >> n >> m;

    //allocate the rows for the 2d vector
    matrix.resize(n); 
    for(size_t i = 0 ; i < matrix.size(); i++ ) { // use size_t 
        matrix[i].resize(m);    
    }

   //For each row, check to see if *m + 1* doubles were read, if not print a message and ask again

   for(size_t i = 0; i < matrix.size(); i++) {
        cout<< "Enter the system matrix one row at a time" << endl;
        cin >> input;
    for(size_t j = 0 ; j < matrix.size(); j ++){
        
    }
   }
   


}
