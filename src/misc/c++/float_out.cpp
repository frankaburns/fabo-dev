#include <cmath>
#include <cstdio>
#include <set>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
   /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

   ifstream file("float.txt");
   if (!file.is_open()) {
      cerr << "Error: Could not open the file.\n";
      return 1;
   }

   int T; file >> T;
   cout << setiosflags(ios::uppercase);
   cout << setw(0xf) << internal;
   while(T--) {
      double A; file >> A;
      double B; file >> B;
      double C; file >> C;
      long long o = A;
      cout << std::fixed; 
      cout << setw(0x0) << "0x" << std::hex << std::nouppercase << o << endl;
      cout << std::showpos;
      cout << std::setfill('_') << std::setw(15) << std::setprecision(2) << std::right << B << endl; 
      cout << std::noshowpos; 
      cout << std::scientific << std::uppercase << std::setprecision(9) << C << std::endl; 
   }   
   return 0;
}
