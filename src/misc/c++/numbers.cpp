#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

int main()
{
    string numbers[10] = {"zero", "one", "two", "three", "four",
                        "five", "six", "seven", "eight", "nine"};
                        
    string n_temp;
    
    getline(cin, n_temp);
    int start = stoi(ltrim(rtrim(n_temp)));
      
    getline(cin, n_temp);
    int end = stoi(ltrim(rtrim(n_temp)));

    for (int n=start; n<=end; n++) {
       if (n < 10) {
           cout << numbers[n] << endl;
       } else {
           printf ("%s\n", (n%2 == 0) ? "even" : "odd");
       }
    }
    // Write your code here

    return 0;
}  

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
