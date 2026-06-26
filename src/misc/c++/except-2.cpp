#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

class Server {
private:
	static int load;
public:
	static int compute(long long A, long long B) {
		load += 1;
		if(A < 0) {
			throw std::invalid_argument("A is negative");
		}
		vector<int> v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if(B == 0) throw 0;
		real = (A/B)*real;
		int ans = v.at(B);
		return real + A - B*ans;
	}
	static int getLoad() {
		return load;
	}
};
int Server::load = 0;

int main() {
	int T; 
        // 1. Open the file stream 
        ifstream file("except.txt");
        if (!file.is_open()) {
           cerr << "Error: Could not open the file.\n";
           return 1;
        }  
	file >> T;
	while(T--) {
		long long A, B;
		file >> A >> B;
        int result = 0;
        try {
            result = Server::compute(A, B);
            cout << result << endl;
        } catch (const std::invalid_argument& e) {
            cout << "Exception: " << e.what() << endl; 
        } catch (const std::bad_alloc& e) {
           cout << "Not enough memory" << endl;
        } catch (const std::exception& e) {
           cout << "Exception: " << e.what() << endl;
        } catch (...) {
        // This block catches absolutely any C++ exception
             cout << "Other Exception" << endl;
        }
        
		/* Enter your code here. */

	}
	cout << Server::getLoad() << endl;
	return 0;
}
