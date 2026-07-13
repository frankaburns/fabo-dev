#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : Cache {
   private:
      int   depth;
      Node *root;
      
   public:
   
      LRUCache () {
         cp    = 5;
         depth = 0;
         tail  = nullptr;
         head  = nullptr;
      }
      
       LRUCache (int cap) {
         cp    = cap;
         depth = 0;
         tail  = nullptr;
         head  = nullptr;
      }
     
      
      void set(int key, int value) {
         head = insert (head, key, value);
         depth++;
         if (tail == nullptr) { tail = head; }
         tail = trimList (tail, depth);
      }
    
      Node *insert(Node *node, int key, int value) {

         bool moved = false;
         Node *tmp;
         Node *n;

         if (node == nullptr) {
            n = new Node(key, value);
            return n;
         }
         
         tmp   = node;
         moved = false;
         while (tmp != nullptr) {
         
         // if key is found and it's not at the top of the list.
         //
            if (tmp->key == key) {
 
               if (tmp != node) {
                  if (tmp->prev != nullptr) tmp->prev->next = tmp->next; 
                  if (tmp->next != nullptr) tmp->next->prev = tmp->prev; 
                  tmp->next = node;

                  if (tmp == tail) {
                     Node *t = tmp->prev;
                     t->next = nullptr;
                     tail = t;
                  }
                  
                  tmp->prev  = nullptr;
                  node->prev = tmp;
               }
               
               tmp->value = value;
               moved = true;
               depth--;
               break;
            }
            tmp = tmp->next;
         }
         
         if (!moved) {  // not moved place at root
            n = new Node(key, value);         
            n->next = node;
            node->prev = n;

         } else {  // didn't find, not in list or list empty
            n = tmp;
         }
         
         return n;
     }
     
     Node *trimList(Node *tail, int depth) {
        Node *tmp;
        if (depth > cp) {
           tmp = tail->prev;
           tmp->next = nullptr;
           delete tail;
           tail = tmp;
        }
        return tail;
     }
     
     int get(int key) {
        return retrieve (head, key);
     }
    
     int retrieve(Node *node, int key) {
        Node *tmp;
        
        tmp = node;
        
        for (int cnt=1; cnt<=depth; cnt++) {
           if (tmp == nullptr) {
              break;
           } else if (tmp->key == key) {
              return tmp->value;
           } else {
              tmp = tmp->next;
           }
        }
        return -1;
    }
};

int main() {
   int n, capacity,i;
   
   ifstream file("cache2.txt");
   if (!file.is_open()) {
      cerr << "Error: Could not open the file.\n";
      return 1;
   }
    
   file >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      file >> command;
      if(command == "get") {
         int key;
         file >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         file >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

