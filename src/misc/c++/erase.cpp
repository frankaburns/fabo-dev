#include <cmath>
#include <cstdio>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n, r1, r2;    
    
    vector<int> a;

    ifstream file("erase.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }

    file >> n;
    
    for (int i=0; i<n; i++) {
       file >> r1;
       a.push_back (r1);
    }
    
    file >> r1;
    a.erase(a.begin()+r1-1);

    for (int i=0; i<a.size(); i++) {
       cout << a[i] << " ";;
    }
    cout << endl;
    
    file >> r1 >> r2;
    a.erase(a.begin()+r1-1, a.begin()+r2-1);
    
    cout << a.size() << endl;
    
    for (int i=0; i<a.size(); i++) {
       cout << a[i] << " ";;
    }
    cout << endl;
    
    return 0;
}
