#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
/*
 We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

Example 1:

input: 
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation: 
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.

Example 2:

Input: 
asteroids = [8, -8]
Output: []
Explanation: 
The 8 and -8 collide exploding each other.

Example 3:

Input: 
asteroids = [10, 2, -5]
Output: [10]
Explanation: 
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.

Example 4:

Input: 
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation: 
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.

*/
enum CollisionType {
     NONE,
     OPPOSITE,
     LEFT,
     RIGHT
};

class Solution {

private:

    std::vector<int>* asteroids;
public:

   Solution(std::vector<int>& vect) {
         asteroids = new std::vector<int>(); // Creates an empty vector on the heap 
        *asteroids = vect;
    }

   ~Solution() {
         delete asteroids; 
    }

    std::vector<int>* getSolution() {
        return asteroids;
    }


    void printAsteroids(std::string greeting) {
        std::cout << greeting << "[";
	try {
            for (auto element = asteroids->begin(); element != asteroids->end(); ++element) {
                std::cout << *element << " ";
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Out of Range: " << asteroids->size(); 
	}
        std::cout << "]" << std::endl;
    }

    void resolveCollision(CollisionType type, int index1, int index2) {
       
        if (type == OPPOSITE) {
           if (abs(asteroids->at(index1)) > abs(asteroids->at(index2))) {
	       asteroids->erase(asteroids->begin()+index2);
           } else if (abs(asteroids->at(index1)) < abs(asteroids->at(index2))) {
	       asteroids->erase(asteroids->begin()+index1);
           } else {
	       asteroids->erase(asteroids->begin()+index2);
	       asteroids->erase(asteroids->begin()+index1);
           }
	} else if (type == RIGHT) {
	    asteroids->erase(asteroids->begin()+index2); 
	    
	} else if (type == LEFT) {
	    asteroids->erase(asteroids->begin()+index1);
	}
    }

    CollisionType isCollision(int a1, int a2) {

	CollisionType collisionType = NONE;

	// The case of a left moving asteroid colliding 
	// with a right moving asteroid
	//
        if (((a1 > 0 && a2 < 0) || (a1 < 0 && a2 > 0)) && (a1 > 0)) {
           collisionType = OPPOSITE;
	// The case of both right moving asteroids colliding 
	// if the higher index is less than the lower, collision.
	//
        } else if ((a1 > 0 && a2 > 0) && (a1 > a2)) {
           collisionType = NONE;
	// The case of both left moving asteroids colliding 
	// if the lower index is less than the higher, collision.
	//
        } else if ((a1 < 0 && a2 < 0) && (abs(a1) < abs(a2))) {
           collisionType = NONE;
        }

       return collisionType;
    }

    void clearTheLine() {
        bool          dirty     = true;
        bool          collided  = true;

	CollisionType collision = NONE;
	  
        unsigned long idx = 0;
	
	printAsteroids("Iterate until Done : ");
        while (dirty) {
            if (idx >= asteroids->size()-1 || asteroids->size() == 0) {
     	        if (!collided || asteroids->size() <= 1) {
	            dirty = false;
		}
		idx       = 0;
		collided  = false;
	    }
	    if (dirty) {
	        if ((collision=isCollision((int)asteroids->at(idx), (int)asteroids->at(idx+1)))) {
                    collided = true;
		    resolveCollision(collision, idx, idx+1);
                }  
	        idx++;
	    }
	}  
	printAsteroids("Done               : ");
    }
};



// To execute C++, please define "int main()"
int main(int argc, char* argv[]) {
    // argc: argument count
    // Represents the number of command-line arguments, including the program name itself.

    // argv: argument vector
    // An array of character pointers (strings), where each pointer points to a command-line argument.
    // argv[0] typically holds the name of the executable.
    // argv[1] and subsequent elements hold the actual arguments provided by the user.


    Solution *solution = 0; 

    std::vector<int> test;
    std::vector<int> test1   = {15, 5, -11, -17, -12};
    std::vector<int> test2   = {10, 12, -5};
    std::vector<int> test3   = {1, 2, -2, -1};
    std::vector<int> test4   = {8, -8};

    std::cout << "" << std::endl;
    std::cout << "Number of arguments: " << argc << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Input Configuration: ["; 

    if (argc >= 2 ) {

        for (int i = 1; i < argc; ++i) {
            test.push_back(std::stoi(argv[i]));
        }

        for (int element : test) {
           std::cout << element << " ";
        }   
        std::cout << "]" << std::endl;
 
        solution = new Solution(test);
    } else {
        for (int element : test2) {
           std::cout << element << " ";
        }   
        std::cout << "]" << std::endl;
 
        solution = new Solution(test2);
    }

    solution->clearTheLine();

    std::vector<int>* result = solution->getSolution();

    std::cout << "Cleared Line       : [";
    for (auto element = result->begin(); element != result->end(); ++element) {
        std::cout << *element << " ";
    }
    std::cout << "]" << std::endl;
    delete solution;
}
