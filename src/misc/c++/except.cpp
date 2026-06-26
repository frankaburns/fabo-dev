#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

/* Define the exception here 
   Inherit from std::runtime_error to leverage its string-handling features */

class BadLengthException : public std::exception {
private:
    std::string full_message;
    int error_code;

public:
    BadLengthException(int code) : error_code(code) {
        full_message = std::to_string(code);
    }

    // The what() method must be marked noexcept and override the base method
    const char* what() const noexcept override {
        return full_message.c_str();
    }

    int getErrorCode() const noexcept {
        return error_code;
    }
};


bool checkUsername(string username) {
	bool isValid = true;
	int n = username.length();
	if(n < 5) {
		throw BadLengthException(n);
	}
	for(int i = 0; i < n-1; i++) {
		if(username[i] == 'w' && username[i+1] == 'w') {
			isValid = false;
		}
	}
	return isValid;
}

int main() {
	int T; cin >> T;
	while(T--) {
		string username;
		cin >> username;
		try {
			bool isValid = checkUsername(username);
			if(isValid) {
				cout << "Valid" << '\n';
			} else {
				cout << "Invalid" << '\n';
			}
		} catch (BadLengthException e) {
			cout << "Too short: " << e.what() << '\n';
		}
	}
	return 0;
}
