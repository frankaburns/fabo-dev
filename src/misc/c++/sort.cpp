#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n, num;    
    
    vector<int> a;

    cin >> n;
    
    a.reserve(n);
    
    for (int i=0; i<n; i++) {
       cin >> num;
       a.push_back (num);
    }
    
    sort(a.begin(),a.end()); 
    
    for (int i=0; i<n; i++) {
       cout << a[i] << " ";;
    }
    cout << endl;
    
    return 0;
}
