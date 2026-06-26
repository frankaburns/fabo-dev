#include <cmath>
#include <cstdio>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    private:
       int id;
       int age;
       int type;
       string name;
   public:
       void set_age (int a) { age = a; }
       void set_id (int n) { id = n; }
       void set_type(int t) { type = t; }
       void set_name(string& n) { name = n; }

       int get_id () { return id; }
       int get_age () { return age; }
       int get_type() { return type; }
       string& get_name() { return name; }
     
       virtual void getdata(ifstream& file) {
       }
     
       virtual void putdata() {
          cout << "I'm a person!" << endl;
       }

};

class Student : public Person {
   private:
      int scores[6];
      static int count;
      
   public:
   
     Student() {
        set_id(++count);
        set_age(0);
        set_type(1);
     }
     
     void getdata(ifstream& file) {
        int a;
        string n;
        file >> n >> a;
        
        set_age(a);
        set_name(n);
        
        for (int i=0; i<6; i++) {
           file >> scores[i];
        }
     }
     
     void putdata() {
        int sum = 0;
        for (int i=0; i<6; i++) {
           sum += scores[i];
        }
        cout << get_name() << " " << get_age() << " " << sum << " " << get_id() << endl; 
     }
};

class Professor : public Person {
   private:
      int numpub;
      static int count;
      
   public:
   
     Professor() {
        set_id(++count);
        set_age(0);
        set_type(2);
        numpub = 0;
     }
     
     void getdata(ifstream& file) {
        int a;
        string n;
        file >> n >> a >> numpub;
        
        set_age(a);
        set_name(n);
     }
     
     void putdata() {
        cout << get_name() << " " << get_age() << " " << numpub << " " << get_id() << endl; 
     }
};

int Student ::count = 0;
int Professor ::count = 0;

int main(){

    int n, val;
 
    ifstream file("school.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }
    
    file>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        file>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(file); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

