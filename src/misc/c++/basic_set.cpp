#include <cmath>
#include <cstdio>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n, q, v;
    
    set<int>s; //Creates a set of integers.

    ifstream file("set.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }

    file >> n;
    
    for (int i=0; i<n; i++) {
       file >> q >> v;
       switch (q) {
          case 1:
             s.insert(v);
             break;
          case 2:
             s.erase(v);
             break;          
          case 3:
             auto itr=s.find(v); //Gives the iterator to the value
             if (itr == s.end()) {
                cout << "No" << endl;
             } else {  
                cout << "Yes" << endl;
             }
             break;          
       }
    }        
    return 0;
}
