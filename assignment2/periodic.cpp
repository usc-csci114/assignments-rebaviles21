#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include <utility>

using namespace std;

struct Element {
	Element() :
	symbol(),name(),number(0),atomic_mass(0.0),type() {};
	
	string symbol; //e.g "H", "He"
	string name; //e.g "Hydrogen", "Helium"
	int number; //e.g 1, 2
	double atomic_mass; //e.g. 1.008, 4.0026
	string phase; //phase at room temp e.g gas, liquid, solid
	string type; //e.g. "metalliod, "transitional metals"
};
struct compclass {
  bool operator() ( pair<string, int> a, pair<string, int> b) { return (a.first < b.first);}
} comp;

//prototype
size_t index_find(vector< pair<string, int> > index, string key);
void printElement(vector <Element> elements, size_t index);

int main(int argc, char* argv[])
{
	// first parse the data that the elements.csv has
	ifstream ifile("elements.csv"); // parse the data

	if(ifile.fail()) {
        cout << "File was unable to be open" << endl;
        return 1; 
    }
	vector <Element> elements(119); 
	vector< pair<string, int > > name_index; // vector pair
	vector< pair<string, int> > symbol_index;
	std::pair<string, int> num;
	std::pair<string, int> sym;

	Element element; // make the struct viable
	string number; // must do because of overload error
	string atomicMass;
	string line;
	string name;
	string symbol;
	
	elements.push_back(element); // adds the intiialized  ctor

	getline(ifile,line); // instruction title line (we dont need it)
    while(getline(ifile,line)) { // grabs the whole line
		stringstream ss (line); // grabs the whole line
		//parse the information for the vector
		getline(ss,number, ','); 
		element.number = stoi(number);
		getline(ss,element.name,',');
		getline(ss,element.symbol,',');
		getline(ss,atomicMass,',');
		element.atomic_mass = stod(atomicMass); 
		getline(ss,element.phase,',');
		getline(ss,element.type,',');

		//add into the element vector
		elements.push_back(element); // this is possible bc they are associated with the struct

		// PAIRS:
		// first make a pair
	
		num.first = element.name;
		num.second = element.number;
		sym.first = element.symbol;
		sym.second = element.number;
		// push back the objects 
		name_index.push_back(num);
		symbol_index.push_back(sym);

		//SORTING
		sort(symbol_index.begin(), symbol_index.end(), comp);
		sort(name_index.begin(), name_index.end(), comp);
	}

	bool wantToQuit = false;
	int userNumber;
	string userInput;
	//string userString;

	while(wantToQuit == false) {
		// want to let in int variable
		cout<< "Which element are you interested in??" << endl;
		// cout<< "Do you want to search for the period element number OR period element name?? N for Number or S for Name" << endl;
		cout << "To quit just write quit" << endl;
		cin >> userInput; //grab the information
		
		if(isdigit(userInput[0])) { // checks the first character to see if it is a value -- number 
			userNumber = stoi(userInput);
			if(userNumber >= 1 or userNumber <= 118) { // within the range of the elements
				cout << "Element Number: " << userNumber;
				printElement(elements,userNumber);
			}
			else{ // out of range 
				cout << "Invalid Range. Element does not exist" << endl;
			}

		}
		// based if it is a string or not
		if(!isdigit(userInput[0])) { // only a string so it should be false
			if(userInput == "quit") { // if the input is a string and equals this
				wantToQuit = true;
				break;
			}
			if(userInput.size() == 1 or userInput.size() == 2 ){ // length of the string size 1
				size_t elementSymbol =index_find(symbol_index,userInput);
				//cout << "Symbol: " << elementSymbol << endl;
				printElement(elements,elementSymbol);
			} 
			else if (userInput.size() > 2 ) { // for the name
				size_t elementName = index_find(name_index,userInput);
				printElement(elements,elementName);	
			}
			else{
			cout << "Not Found!" << endl;
			}
		}
		cout<< "Do you want to search for the period element number OR period element name?? N for Number or S for Name" << endl;
		cin >> userInput; 
	}
	
}

//function:
size_t index_find(vector< pair<string, int> > index, string key) {
	//needs to be binary search (??)
	int left = 0; 
	int right = index.size()-1;
	while(left <= right) {
		int mid = left+(right-left);
		mid = mid/2;
		if(index[mid].first < key) { 
			left = mid+1;
		}
		else if(index[mid].first > key) {
			right = mid -1; 
		}
		if (index[mid].first == key) {
			return index[mid].second;
		}
	}
	return -1;
	
}

void printElement(vector <Element> elements, size_t index) {
	cout << "Name: "<< elements[index].name << endl;
	cout<< "Symbol: " << elements[index].symbol << endl;
	cout << "Atomic Mass: " << elements[index].atomic_mass << endl;
	cout<< "Phase: " << elements[index].phase << endl;
	cout <<"Type: " << elements[index].type << endl; 
}


// the index is not printing