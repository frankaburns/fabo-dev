#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

class attribute {
   private:
      string name;
      string value;
    
   public:
      attribute (string str, string val) {
          name = str;
          value = val;
      }
      
     ~attribute() {}
   
     void setName (string str) { name = str; }
     void setValue (string str) { value = str; }
      
     string getName () { return name; }
     string getValue () { return value; }
};

class section {
   private:
     bool                 complete;
     string               name;
    
     section             *next;
     vector<attribute *>  attr;

   public:
     section(string str) {
        name     = str;
        next     = nullptr;
        complete = false;
     }
        
     section(string str, vector<attribute *>& attributes) {
        name     = str;
        next     = nullptr;
        attr     = attributes;
        complete = false;
     }
        
     ~section() {}

     section *addTag (section *root, section *tag) {
        if (root == nullptr) {
           root = tag;
        } else {
           root->next = addTag (root->next, tag);
        }
        return root;
     }
     void setTagComplete(string line, section *root) {
        if (root != nullptr) {
           if (root->name.compare(line) == 0) {
              root->complete = true;
           } else {
              setTagComplete (line, root->next);
           }
        } else {
           printf ("No such Tag: %s\n", line.c_str());
        }
     }

     bool is_complete() { return complete; }
     
     string getName() { return name; }
     
     string getAttribute (int index) {
        return attr[index]->getValue();
     }
     string getAttrByName (string str) {
        for (int idx=0; idx<attr.size(); idx++) {
           if (attr[idx]->getName().compare(str) == 0) {
              return attr[idx]->getValue();
           }
        }
        return "";     
     }
     
     section *getNext() { return next; }
};

class markDown {
   private:
     char begin  = '<';
     char end    = '>';
     char dot    = '.';
     char dash   = '-';
     char slash  = '/';
     char tilde  = '~';
     char equals = '-';

     
     vector<section *> doc;

     void getAttributes(string line, vector<attribute *>& attrVect) {
        int  nameCount = 0;
        int  valueCount = 0;
        
        char name[25];
        char value[25];
        
        bool noName  = true;

        attribute *attr = nullptr;
        
        memset (name, 0, 25);
        memset (value, 0, 25);
        
        for (int idx=0,nameCount=0,valueCount=0; idx<line.size(); idx++) {
           if (noName) {
              if (line[idx] == ' ') {
                 continue;
              } else if (line[idx] == '=') {
                 noName = false;
              } else {
                 name[nameCount++] = line[idx];
              }
           } else {
              if (line[idx] == ' ' || line[idx] == '>') {
                 if (valueCount == 0) {
                    continue;
                 } else {
                    attr = new attribute(name, value);
                    attrVect.push_back(attr);
                    
                    noName = true;
                    
                    nameCount  = 0;
                    valueCount = 0;
                    
                    memset (name, 0, 25);
                    memset (value, 0, 25);
                 }
              } else {
                 value[valueCount++] = line[idx];
              }
           }
        }
     }   
           
     // Parse the line either a tag with attributes or a close tag      
     //
     section *parseLine (section *root, string line) {
        int   idx = 0;
  
        char tagName[25];
     
        section            *tag;
        vector<attribute *> attr;

        idx = 1;
        memset (tagName, 0, 25);
        if (line[0] == '<') {
           if (line.compare(0, 2, "</") == 0) {
              int size = line.size() - 2 - 1;
              string endTag = line.substr(2, size);
              root->setTagComplete(endTag, root);
           } else {
              int nameIdx = 0;
              while (line[idx] != ' ') {
                tagName[nameIdx++] = line[idx++];
              }
                 
              int size = line.size() - idx;
              string attrStr = line.substr(idx, size);
              getAttributes(attrStr, attr);

              string tagStr(tagName);
              if (root == nullptr) {
                 root = new section(tagStr, attr);
	      } else {
	         root = root->addTag(root, new section (tagStr, attr));
	      }
	   }
        } else {
           printf( "Protocol error: %s\n", line.c_str());
        }
        return root;
     }
   public:

     string   str;
     section *tag = nullptr;

     markDown(int lines, ifstream& file) {
        string address;

        for (int i=0; i<lines; i++) {
           getline(file, address); // Now safely reads the full string with spaces
           cout << address << endl;
           tag = parseLine(tag, address);
           if (tag->is_complete()) {
              doc.push_back(tag);
              tag = nullptr;
           }    
        }
     }
     ~markDown() {}
     
     void processQueries(int queries, ifstream& file) {
        string address;
        for (int i=0; i<queries; i++) {
           getline(file, address); // Now safely reads the full string with spaces
           cout << address << endl;
           findAttribute(address);
        }
     }
  
     void findAttribute(string line) {
        // Count occurrences
        string   tag;
        section *sect = nullptr;
        
        size_t posDot   = -1;
        size_t posTilde = -1;
 
        ptrdiff_t cnt = count(line.begin(), line.end(), dot);

        posDot   = line.find(dot);
        posTilde = line.find(tilde);
        
        if (posDot != std::string::npos) {
           tag = line.substr(0, posDot);
        } else {
           tag = line.substr(0, posTilde);
        }
        for (int idx=0; idx<doc.size(); idx++) {
           if (tag.compare(doc[idx]->getName()) == 0) {
              sect = doc[idx];
           }
        }
        if (sect != nullptr) {
           if (posDot != std::string::npos) {
              string tag = line.substr(posDot+1, posTilde);
              string value = line.substr(posTilde+1, line.size()-posTilde-1);
              printf ("B: found name: %s, value: %s\n", sect->getNext()->getName().c_str(), value.c_str());
           } else {
              string value = line.substr(posTilde+1, line.size()-posTilde-1);
              printf ("A: found name: %s, value: %s\n", sect->getName().c_str(), value.c_str());
           }
        }
    }
};

int main() {

  int    lines;
  int    queries;
  
  string str;
  
  // 1. Open the file stream
  ifstream file("3-tag.txt");
  if (!file.is_open()) {
     cerr << "Error: Could not open the file.\n";
     return 1;
  }

  file >> lines >> queries;
  getline(file, str);
  markDown *md = new markDown(lines, file);
  md->processQueries(queries, file);
  
  return 0;
}
