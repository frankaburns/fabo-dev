#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

vector<int> parseInts(string str) {
    
    vector<int> values;
	// Complete this function
    // Create a stringstream object 
    // to str
    stringstream ss(str);
    
      // Temporary object to store 
      // the splitted string
    string t;
  
      // Delimiter
    char del = ',';

       // Splitting the str string 
       // by delimiter
    while (getline(ss, t, del)) {
        values.push_back(std::atoi(t.c_str()));
    }
  
    return values;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}
