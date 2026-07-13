#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

/*
3
fire 5
AquaVitae 999 AruTaVae
frost 7
*/

void counterspell(Spell *spell) {

  /* Enter your code here */
   if (typeid(*spell) == typeid(Fireball)) {
      ((Fireball *)spell)->revealFirepower();
   } else if (typeid(*spell) == typeid(Frostbite)) {
      ((Frostbite *)spell)->revealFrostpower();   
   } else if (typeid(*spell) == typeid(Waterbolt)) { 
      ((Waterbolt *)spell)->revealWaterpower();   
   } else if (typeid(*spell) == typeid(Thunderstorm)) { 
      ((Thunderstorm *)spell)->revealThunderpower();
   } else {
      string seq = "";
      string str1;
      string str2;

      str1 = spell->revealScrollName();
      str2 = SpellJournal::journal;
      
      int s1 = 0;
      int s2 = 0;
      int big = 0;
      
      while (s1 < str1.size()) {
         for (int i=s1; i<str1.size()+s1+1; i++) {;;         
            for (int j=s2; j<str2.size(); j++) {
               if (str1[i%str1.size()] == str2[j]) {
                  s2 = j+1;
                  seq += (char)str1[i%str1.size()];
                  break;
               }
            }
         }
         
         if (big < seq.size()) { 
            big = seq.size(); 
         }
         
         // cout << seq << " s1: " << s1 << endl;
         s1++;
         s2 = 0;
         seq.clear();
      }
      cout << endl;      
      cout << big << endl;
   }
}

class Wizard {
    public:
        Spell *cast(ifstream& file) {
            Spell *spell;
            string s; file >> s;
            int power; file >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                file >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    
    ifstream file("magic.txt");
    if (!file.is_open()) {
       cerr << "Error: Could not open the file.\n";
       return 1;
    }

    file >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast(file);
        counterspell(spell);
    }
    return 0;
}
