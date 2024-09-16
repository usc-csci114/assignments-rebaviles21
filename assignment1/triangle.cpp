#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    double x1,y1;
    double x2,y2;
    double x3,y3;

    string userInput;

    cout << "Enter the points of the triangle using a coordinate system using doubles(x,y). To quit the program: enter 'quit'. " << endl;
    cin >> userInput;
    if(userInput == "quit") {
        cout<< "Quit message. Goodbye! " << endl;
        return 0;   
    }
    if(cin.fail()) {
        cout << "Error: One or more of these numbers was not inputted properly" << endl;
        return 1;
    }
    //once everything is confirmed to be valid (convert the original string to a double--casting)
    x1 = stoi(userInput);
    cin >> y1 >>x2 >> y2 >> x3 >>y3;

    double area = abs(0.5*(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)));
    cout << "The area of the triangle: " << area << endl;

   return 0;  
}

