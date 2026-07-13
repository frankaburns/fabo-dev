#include <cmath>
#include <cstdio>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

/*Write the class AddElements here*/
template <typename T>
class AddElements {
private:
    T data; // T can be an int, double, std::string, etc.
    string my_str;

public:
    // Constructor
    AddElements(T value) : data(value) {}

    // Getter method
    T getData() const {
        return data;
    }

    T add(T val) const {
        return data+val;
    }
    
    string& concatenate(string& str) {
        my_str = (string)data + str;
        return my_str;
    }
    
    // Setter method (defined outside the class for demonstration)
    void setData(T value) {
        data = value;
    }
};

int main () {
  int n,i;
    
  ifstream file("temp.txt");
  if (!file.is_open()) {
     cerr << "Error: Could not open the file.\n";
     return 1;
  }     
      
  file >> n;
  for(i=0;i<n;i++) {
    string type;
    file >> type;
    if(type=="float") {
        double element1,element2;
        file >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        file >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        file >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}

