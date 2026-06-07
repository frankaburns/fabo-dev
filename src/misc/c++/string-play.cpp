#include <iostream>
#include <string>

using namespace std;

int main() {
	// Complete the program
    
    string a;
    string b;
    string aPrime;
    string bPrime;
    
    cin >> a;
    cin >> b;

    aPrime = a;
    bPrime = b;
    
    aPrime[0] = b[0];
    bPrime[0] = a[0];
    
    cout << a.size() << " " << b.size() << endl;
    cout << a << b << endl;
    cout << aPrime << " " << bPrime << endl;

    return 0;
}
