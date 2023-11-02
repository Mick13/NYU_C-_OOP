#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*Mickey Shamah
HW 3*/

// same code as other file but the output operators for my classes
//are moved after main

// Define the Warrior class
class Warrior{
    // Make the output operator a friend so that it can access the private member variables of Warrior objects
    friend ostream & operator<< (ostream & os, const Warrior & fight);
private:
    // Define the Weapon class as a private member of Warrior
    class Weapon {
        // Make the output operator a friend so that it can access the private member variables of Weapon objects
            
        friend ostream & operator<< (ostream & os, const Weapon & ww);
    public:
         // Define a constructor for Weapon
        Weapon(const string& weapon_name, int w_strength) : weapon_name(weapon_name), w_strength(w_strength){}
        // Define accessor functions for Weapon
        int getWstrength() const{return w_strength;}
        // Define a function that reduces the strength of a Weapon  
        void fight(int reduceBy) {
            w_strength = w_strength-reduceBy;
            // if the new strength is negative, just make it 0
            if (w_strength < 0){
                w_strength = 0;}
        }
    private:
        // Define private member variables of Weapon
        string weapon_name;
        int w_strength;
    };
    // because the weapn clsss is private, the output operator has to -
    //be both in the class and outside the class
    friend ostream & operator<< (ostream & os, const Weapon & ww);
    
public:
    
    // Define a constructor for Warrior
    Warrior(const string& name, const string& weapon, int strength): name(name), weapon(weapon,strength) {}
private:

    // Define private member variables of Warrior
    string name;
    Warrior::Weapon weapon;
        
public:

    // Define getter methods
    //(using the getters in the) weapon class
    int getWstrength() const {return weapon.getWstrength();}
    // getter is just retuning name from the warrior class
    string getName() const {return name;}  
    //calls the fight function in the weapon subclass
    void battle(int reduceBy) {weapon.fight(reduceBy);}
    
    // method to simmulate a fight between warriors
    void kill(Warrior& opponent){
        cout << name << " battles " << opponent.name << endl;
        
        // if the strength of both are 0 print "Oh, NO! They're both dead! Yuck!"
        if (weapon.getWstrength()  == 0 and opponent.getWstrength() == 0){
            cout << "Oh, NO! They're both dead! Yuck!"<<endl;
            return;}
            
        // if "self" has a strength of 0,the opponent wins
        if (weapon.getWstrength() == 0){
            cout << "He's dead, " << opponent.getName()<<endl;
            return;}
            
        // if opponent has a strength of 0, "self" wins 
        if (opponent.getWstrength()  == 0){
            cout << "He's dead, " << name <<endl;
            return;}
            
        // if the both have non 0 strengths
        
        //if self has a greator strength than opponent. 
        // set the strength of self to strength of self - strength of opponent
        // set the strength of opponent to strength of opponent- strength of self
        // if the strength is less than 0 the battle method will make it 0
        if (weapon.getWstrength() > opponent.getWstrength()){
            weapon.fight(opponent.getWstrength());
            opponent.battle(weapon.getWstrength());
            
            // cout self defeats opponent
            // use getter of opponent
            cout << name << " defeats " << opponent.getName() << endl; }
            
        // if opponent has a greator strength than self
        // set the strength of opponent to strength of opponent- strength of self
        // set the strength of self to strength of self - strength of opponent
        // if the strength is less than 0 the fight method will make it 0
        
        else if (weapon.getWstrength() < opponent.getWstrength()){
            opponent.battle(weapon.getWstrength());
            weapon.fight(opponent.getWstrength());
            //cout opponent defeats self
            // use getter to access opponent's name
            cout << opponent.getName() << " defeats " << name << endl;}
            
        // if they are the same
        else if (weapon.getWstrength() == opponent.getWstrength()){
            // cout "Mutual Annihilation: " nsmr of self and opponent both die
            cout<<"Mutual Annihilation: "<<name<<" and "<<opponent.getName()<<" die at each other's hands\n";
            // set both strengths to 0 by subtracting their strengths form their strengths
            opponent.battle(opponent.getWstrength());
            weapon.fight(weapon.getWstrength());}
    }
};

       
       
// Define a function that finds a Warrior in a vector of Warriors by name
size_t find(const vector <Warrior>& war, const string& name);

// Define the fight function to simulate a battle between two warriors 
void fight(vector <Warrior>& war, const string& name, const string& challanger);

//Define a populate function to ppulate a vector of Warrior types
void populate(const string& name,const string& weapon_name, int strength, vector<Warrior>& prev_war);


int main(){
  ifstream file ("warriors.txt");
  // Create an input file stream to read in from warriors.txt
  // If the file cannot be opened, display an error message and exit
  if (!file)
    {
      cerr << "Couldnt Find warriors.txt";
      exit (1);
    }

  // Vector of warriors to store warrior objects
  vector < Warrior > war;
  
  // creating varibles to read the file into
  
  string command;
  int strength;
  string name;
  string weapon_name;
  string challanger;
  
  // Read in input from the file and execute commandS
  
  while (file >> command){
      if (command=="Status"){
          
        // Display the number of warriors in the vector and the information about each warrior  
        cout << "There are: "<< war.size()<<" warriors"<<endl;
        for (size_t i = 0; i<war.size(); i++){
            if (war.size()-i >1){
                cout<<war[i];
            }
            else{
                cout<<war[i];
            }
        }
        // Define output operator in class to print warrior information
      }
      
      else if (command == "Warrior"){
          // read the values on the line and assign them to variables
          // Call the populate function to add the new warrior to the vector
          file >> name >> weapon_name>> strength;
          populate(name, weapon_name, strength, war);}
          
          
    
      else if (command == "Battle"){
          file >> name >> challanger;
           // Call the fight function to execute the battle between two warriors
          fight(war, name, challanger);}
    }
      
    // close file
    file.close();
  
  }
  
  
// output operator for the Warrior class
// this output is calling the output from the weapon class. (fight.weapon)
ostream & operator<< (ostream & os, const Warrior & fight){
    // its a friend so it can access private attributes of Warrior
  os << "Warrior: " << fight.name << ','<<fight.weapon<<endl;
  // one problem. cannot clear last new line
  return os;}

ostream & operator<< (ostream & os, const Warrior::Weapon & ww){
    // its a friend so it can access private attributes of Weapon
    os << " weapon: " << ww.weapon_name <<", "<<ww.w_strength;
    return os;
       }
  
  
  
// Define a function that finds a Warrior in a vector of Warriors by name 
size_t find(const vector <Warrior>& war, const string& name){
    
    // iterate though the vector or warriors
    for (size_t i = 0; i<war.size(); i++){
        // if you found the name of the warrior in the vector
        if (war[i].getName() == name){
            //retunr the index
            return i;
                }
    }
    // if not return the size of the vector
    return war.size();
}
  
  

// Define the fight function to simulate a battle between two warriors  
void fight(vector <Warrior>& war, const string& name, const string& challanger){
    
  // Find the index of the attacker and the defender using find function
  size_t attacker_index = find(war, name);
  size_t defender_index = find(war, challanger);
  
  // If the attacker or defender is not found in the vector, display error message and return
  if (attacker_index == war.size() || defender_index == war.size()){
      cerr<<"Could not find at least one of the fighters"<<endl;
      return;
  }
  
  // Call the kill method in the Warrior class to simulate the battle
  war[attacker_index].kill(war[defender_index]);
}

//Define a populate function to populate a vector of Warrior types
void populate(const string& name,const string& weapon_name, int strength, vector<Warrior>& prev_war){
    // checking if uniqe
    for (const Warrior& player: prev_war){
        if (player.getName()==name){
                //if its not unique display error messege and return
                cerr << name << " already exists!!!" << endl;
	            return;}
        }
    // if it is unique add to vector
    // initilize type Warrior in one line
    prev_war.push_back(Warrior(name,weapon_name,strength));
    
}

