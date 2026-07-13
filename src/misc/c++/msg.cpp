#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Message {
public: 
    string msg;
    string msg_data;
    
    Message() {}
    Message (string& str) {
    
       // Set width to 2 and pad with '0'
       msg = str.substr(2, str.size()-2);
       msg_data = str;        
    }
    
    // Overloading the < operator
    bool operator<(const Message& other) const {
        int   me = stoi(this->msg_data.substr(0, 2));
        int them = stoi(other.msg_data.substr(0, 2));

        return me < them;
    }
    
    const string& get_text() {
       return msg;
    }
};

class MessageFactory {
public:
    int count;
    string value;    

    MessageFactory() {
        count = 0;
    }
    string& make_index() {
       char number[3];
       
       if (count > 9) {
          number[0] = (char)((count/10)+48);
          number[1] = (char)((count%10)+48);
       } else {
          number[0] = '0';
          number[1] = (char)(48+count);
       }
       number[2] = 0;
       value = number;
       
       return value;
    }
    
    Message create_message(const string& text) {
       string ss;
       ss = make_index() + text;
       Message msg = Message(ss);
       count++;
       return msg;
    }
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    
    ifstream file("msg.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }     
    
    while (getline(file, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}

