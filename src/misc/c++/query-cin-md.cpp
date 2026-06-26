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
    
     vector<section *>    next;
     vector<attribute *>  attr;

   public:
     section(string str) {
        name     = str;
        complete = false;
     }
        
     section(string str, vector<attribute *>& attributes) {
        name     = str;
        attr     = attributes;
        complete = false;
     }
     
     section(section *cpy) {
        name     = cpy->getName();
        next     = cpy->getNext();
        attr     = cpy->attr;
        complete = cpy->is_complete();
     }
     
     ~section() {}

     void addTag (vector<section *>& root, section *tag) {
        if (root.empty()) {
           root.push_back(tag);
        } else {
           for (int idx=0; idx<root.size(); idx++) {
              if ( root[idx]->is_complete() ) {
                 if (idx+1 == root.size()) { 
                    root.push_back(tag); 
                    break;
                 } else { 
                    continue;
                 }
              } else { 
                 addTag (root[idx]->next, tag);
              }
           }
        }
     }
      
     vector<section *>& getNext() { return next; }
     
     section *getSectionByName (string str) {
        for (int idx=0; idx<next.size(); idx++) {
           if (next[idx]->getName().compare(str) == 0) {
              return next[idx];
           }
        }
        return nullptr;     
     }
     
     void setTagComplete(string line, vector<section *>& root) {
        if (!root.empty()) {
           for (int i=0; i<root.size(); i++) {
              if (root[i]->name.compare(line) == 0) {
                 root[i]->complete = true;
                 break;
              } else {
                 setTagComplete (line, root[i]->next);
              }
           }
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
        return "Not found!";     
     }
     
     vector<attribute *> getAttributes () {
        return attr;
     }
};

class markDown {
   private:
     char begin  = '<';
     char end    = '>';
     char dot    = '.';
     char dash   = '-';
     char blank  = ' ';
     char slash  = '/';
     char quote  = '"';
     char tilde  = '~';
     char equals = '=';
     
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
              if (line[idx] == blank) {
                 continue;
              } else if (line[idx] == equals) {
                 noName = false;
              } else {
                 name[nameCount++] = line[idx];
              }
           } else {
              if (line[idx] == blank || line[idx] == end || line[idx] == quote) {
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
     void parseLine (vector<section *>& root, string line) {
        int  idx = 0;
  
        char tagName[25];
     
        vector<attribute *> attr;

        idx = 1;
        memset (tagName, 0, 25);
        if (line[0] == '<') {
           if (line.compare(0, 2, "</") == 0) {
              int size = line.size() - 2 - 1;
              string endTag = line.substr(2, size);
              if (!root.empty()) {
                 root[0]->setTagComplete(endTag, root);
              }
           } else {
              int nameIdx = 0;
              while (line[idx] != ' ') {
                tagName[nameIdx++] = line[idx++];
              }
                 
              int size = line.size() - idx;
              string attrStr = line.substr(idx, size);
              getAttributes(attrStr, attr);

              string tagStr(tagName);
              if (root.empty()) {
                 root.push_back(new section(tagStr, attr));
	      } else {
                 root[0]->addTag(root, new section (tagStr, attr));
	      }
	   }
        } else {
           printf( "Protocol error: %s\n", line.c_str());
        }
     }
   public:

     string   str;
     section *tag = nullptr;

     markDown(int lines) {
        string address;

        for (int i=0; i<lines; i++) {
           getline(cin, address); // Now safely reads the full string with spaces
           // cout << address << endl;
           parseLine(doc, address);
        }
     }
     ~markDown() {}
     
     vector<section *>& getDoc() {
        return doc;
     }
     
     void processQueries(int queries) {
        string address;
        for (int i=0; i<queries; i++) {
           getline(cin, address); // Now safely reads the full string with spaces
           // cout << address << endl;
           findAttribute(address);
        }
     }
  
     void findAttribute(string line) {
        // Count occurrences
        string   tag;
        section *tmp  = nullptr;
        section *sect = nullptr;        
        
        bool   rightPlace = false;
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
           rightPlace = true;
           section *tmpSect = new section(sect);
           string tmpLine = line.substr(0, line.size());
           while (posDot != std::string::npos && tmpSect != nullptr) {
              tmpLine = tmpLine.substr(posDot+1, tmpLine.size());
              posDot  = tmpLine.find(dot);
              if (posDot != std::string::npos) {
                 tag = tmpLine.substr(0, posDot);
              } else {
                 posTilde  = tmpLine.find(tilde);
                 tag = tmpLine.substr(0, posTilde);
              }
              tmpSect = tmpSect->getSectionByName(tag);
              if (tmpSect == nullptr) {
                 rightPlace = false;
                 break;
              }
           }
           
           if (rightPlace) {
              posTilde = line.find(tilde);
              string key = line.substr(posTilde+1, line.size()-posTilde-1);
              if (tmpSect->getAttrByName(key).find("Not Found!") != 0) {
                 printf ("%s\n", tmpSect->getAttrByName(key).c_str());
              } else {
                 printf ("Not Found!\n");
              }
           } else {
              printf ("Not Found!\n");
           }
        } else {
           printf ("Not Found!\n");
        }
    }

     void printAttributes (vector<attribute *> attr) {
        for (int idx=0; idx<attr.size(); idx++) {
           printf ("%s = %s ", attr[idx]->getName().c_str(), attr[idx]->getValue().c_str());
        }
        printf (">\n");
     }
      
     void printSection (vector<section *>& root) {
        if (root.empty()) {
        } else {
           for (int i=0; i<root.size(); i++) {
              printf ("<%s ", root[i]->getName().c_str());
              printAttributes(root[i]->getAttributes());
              printSection (root[i]->getNext());
           }
        }
     }
};

int main() {

  int    lines;
  int    queries;
  
  string str;
  
 cin >> lines >> queries;
  getline(cin, str);
  markDown *md = new markDown(lines);
  md->printSection(md->getDoc());
  md->processQueries(queries);
  
  return 0;
}
