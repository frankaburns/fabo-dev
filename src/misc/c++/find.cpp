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

    int n, s, c;
    bool found = false;
    
    vector<int> a;

    ifstream file("find.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }

    file >> n;
    
    for (int i=0; i<n; i++) {
       file >> s;
       a.push_back (s);
    }
    
    file >> n;
    
    for (int i=0; i<n; i++) {
       c     = -1;
       found = false;
       file >> s;
       // Step 2: Perform fast O(log n) binary  search
       auto it = lower_bound(a.begin(), a.end(), s);

       // Step 3: Verify the element matches the target
       if (it != a.end() && *it == s) {
          cout << "Yes " << it-a.begin()+1 << endl;
       } else {
          cout << "No " << it-a.begin()+1 << endl;
       }
    }
        
    return 0;
}
