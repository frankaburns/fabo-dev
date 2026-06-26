#include<bits/stdc++.h>

using namespace std;
//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 

// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)
class Box {
    private:
    int l;
    int b;
    int h;
    long long volume;
    public:

// Constructors: 
    Box() {
        l = 0;
        b = 0;
        h = 0;
        volume = 0;
    }
    
    Box(int length,int bredth,int height) {
        l = length;
        b = bredth;
        h = height;
        volume = (long long)l*b*h;
    }

    Box(Box& box) {
        l = box.l;
        b = box.b;
        h = box.h;
        volume = box.volume;
    }

    int getLength() { return l; } // Return box's length
    int getBreadth () { return b; } // Return box's breadth
    int getHeight () { return h; }  //Return box's height
    long long CalculateVolume() {
        volume = (long long)l*b*h;
        return volume;
    } // Return the volume of the box
  
    // Copy Assignment Operator
    Box& operator=(const Box& box) {  
        // 1. Self-assignment check
        if (this == &box) {
            return *this; 
        }

        // 2. Copy the data (Deep Copy)
        
        l = box.l;
        b = box.b;
        h = box.h;
        volume = box.volume;
        // 4. Return a reference to the current object
        return *this;
    }
    
    // Overloading the > operator
    bool operator<(const Box& other) const {
       bool greater = false;
       if (this->l < other.l) {
          greater = true;
       } else if (this->l == other.l && this->b < other.b) {
          greater = true;
       } else if (this->l == other.l && this->b == other.b && this->h < other.h) {
          greater = true;
       }
       return greater;
    }
    
    // Overloading friend function to allow: std::cout << pointInstance;
    friend std::ostream& operator<<(std::ostream& os, const Box& box) {
        os << box.l << " " << box.b << " " << box.h;
        return os; 
    }
};


void check2()
{
	int n;
        ifstream file("box.txt");
        if (!file.is_open()) {
           cerr << "Error: Could not open the file.\n";
           exit (1);
        }  
	file>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		file>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			file>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			file>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}
