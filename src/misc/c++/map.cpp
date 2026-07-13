#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n, q, v;
    
    char   name[25];
    
    map<string,int>m; //Creates a map m where key_type is of type string and data_type is of type int.

    cout << "Opening file!" << endl;
    FILE *file = fopen("./map.txt", "r");
    if (!file ) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }
    cout << "File open!" << endl;
    fscanf (file, "%d\n", &n);
    cout << "Queries: " << n << endl;    
    
    for (int i=0; i<n; i++) {
       memset (name, 0, sizeof(name));
       fscanf(file, "%d %s ", &q, name);
       cout << "Query: " << q << " Key: " << name << endl;
       auto itr=m.find(name); //Gives the iterator to the value       
       switch (q) {
          case 1:
             fscanf (file, "%d\n", &v);
             if (itr != m.end()) {
                m[name] += v;
             } else {
                m.insert(make_pair(name,v));
             }
             break;
          case 2:
             m.erase(name);
             break;          
          case 3:
             if (itr == m.end()) {
                cout << "0" << endl;
             } else {  
                cout << m[name] << endl;
             }
             break;          
       }
    }        
    return 0;
}
