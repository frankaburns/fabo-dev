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
    long long modulo31 = 2147483647LL;
    long long n, s, p, q;
    vector<long long> a;
    
    ifstream file("bitarray.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }
    
    file >> n >> s >> p >> q;;    
    
    a.push_back (s & modulo31 );
    for (int i=1; i<n; i++) {
       a.push_back ((a[i-1]*p+q) & modulo31);
    }
    for (int i=0; i<n; i++) {
       cout << "a[" << i << "] = " << a[i] << endl;
    }
    
    return 0;
}
