/*
  hw04_start.cpp
  modified!
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.

// Class Warrior
class Warrior{
    
    //defines the output operator as a friend of the class so it can access the private attirbutes
    friend ostream & operator << (ostream & os, const Warrior& warrior){
        os << "\t" << warrior.name<<": " <<warrior.strength;
        return os;
    }  
// Declares that the following member functions and variables are accessible from outside the class.   
public:

    //Defines a constructor that takes a const reference to a string for the warrior's name,
    // and an integer for the warrior's strength. 
    Warrior(const string& name, int strength) : name(name), strength(strength), hired(false), dead(false){}
    
//Defines public member functions for the Warrior class:
// these functions either get or set private member variables of the warrior class
// will be used in noble class
    bool employed() const {return hired;}
    bool death() const {return dead;}
    void hire() {hired = true;}
    const string& get_name() const {return name;}
    double get_strength() const {return strength;}
    void set_strength(int value) {
        // if the value is 0 make the Warrior dead!
        strength = value;
        if (value==0){
            dead = true;
        }
    }
    void fire() {hired = false;}
    void kill() {dead = true;}
    private:
//Defines the private member variables of the Warrior class: name, strength, hired, and dead.
    string name;
    double strength;
    bool hired;
    bool dead;
};


// Class Warrior
class Noble {
    
    //defines the output operator as a friend of the Noble class so it can access the private attirbutes
    // it iterates through the vector of pointers, derefrence each adress
    //and calls the output operator of each Warrior type
    friend ostream & operator << (ostream & os, const Noble& noble){
        os << noble.noble_name << " has an army of "<<noble.army.size() <<endl;
        for (size_t i = 0; i<noble.army.size(); i++){
            os<<*(noble.army[i]) << " \n"[i != noble.army.size() - 1];
            //TA helped me out with " \n"
        }
        return os;
    }
    
public:

    //Defines a constructor that takes a const reference to a string for the noble's name,
    // and an integer for the noble's strength. 
    Noble(const string& noble_name) : noble_name(noble_name), strength_total(0), dead(false){}
    
 
//public methods and attributes   

    // Define a function "hire" to hire a warrior.
    bool hire (Warrior& warrior){
        
        // Check if the noble is dead
        if (dead == true){
            cout << noble_name<< " failed to hire "<<warrior.get_name()<<endl;
            return false;
        }
        
        // no need to check if the warrior is dead
        
         // If the warrior is not hired, add the warrior to the army
         
         //not dead and not employed
        else if (warrior.employed() == false && warrior.death() == false){
            // add the address of the warrior to the army
            army.push_back(&warrior);
            warrior.hire();
            strength_total += warrior.get_strength();
            return true;
        }
        else{
            // If the warrior is already hired by another noble return false
            cout << noble_name<< " failed to hire "<<warrior.get_name()<<endl;
            return false;
        }
    }
    // Define a function "fire" to fire a warrior from the army.
    bool fire (Warrior& warrior){
        // Check if the noble is dead
        // Check if the Warrior is dead
        // cant fire dead warrior
         if (warrior.death() == true || dead == true){
            cout << noble_name<< " failed to fire "<<warrior.get_name()<<endl;
            return false;
        }
        // Search the army for the warrior
        // found indicates if the warrior was found in the vector
        bool found = false;
        
        for (size_t i = 0; i < army.size(); i++){
            if (army[i] == &warrior) {
                //derefrence warrior
                found = true;
                // must iterate though vector to remove Warrior
                // preventing a memory leak
                army[i] = nullptr;
                for(size_t j = i; j < army.size()-1; j++){
                    army[j] = army[j+1];
                }
                army.pop_back();
            }
                
        }
         // if the warrior is found in the army, fire the warrior 
        if (found == true){
            warrior.fire();
            // remove its strength form the total strength of the Noble
            strength_total -= warrior.get_strength();
            
            //output response
            cout <<warrior.get_name()<<" , you don't work for me any more! -- "
            <<noble_name<<"."<<endl;  
            return true;
    }
    
        // If the warrior is not found in the army, return false
        else{
            cout << noble_name<< " failed to fire "<<warrior.get_name()<<endl;
            return false;
        }
    }
    
    // Define a function "battle" to initiate a battle between two nobles.
    void battle (Noble& enemy){
        
        // print the name of the nobles in battle
        cout << noble_name<< " battles " << enemy.noble_name <<endl;
        
        // if both already dead print out
        if (dead == true && enemy.dead == true){
            cout <<"Oh, NO!  They're both dead!  Yuck!"<<endl;
        }
        // If this noble is already dead and the enemy noble is stronger print message
        else if  (strength_total < enemy.strength_total && dead == true ){
            cout <<"He's dead, " << enemy.noble_name<<endl;
        }
        
        // If the enemy noble is already dead and this noble is stronger print message
        else if (strength_total > enemy.strength_total && enemy.dead== true ){
            cout <<"He's dead, " << noble_name<<endl;
        }
        
        // If both nobles have equal strength, they kill each other
        else if (strength_total == enemy.strength_total){
            cout <<"Mutual Annihilation: "<<noble_name <<" and "<< enemy.noble_name
            <<"die at each other's hands"<<endl;
            // set the total strength of both nobles to 0
            strength_total  = 0;
            enemy.strength_total = 0;
            
            // call the set_strength function to iterate through both vectors
            //and set each Warrior strength to 0
            enemy.set_strength(0);
            set_strength(0);
            
            // set both 
            dead = true;
            enemy.dead = true;
            
            
            // call set strength function
        }
        
        // if noble's strength is greater that enemy's strength
        else if (strength_total > enemy.strength_total){
            // print out message
            cout <<noble_name <<" defeats "<< enemy.noble_name<<endl;
            
            // call the set_strength method to set all the warriors' strength 
            set_strength(strength_total*(1-enemy.strength_total/strength_total));
            // based on specification
            //strength_total*(1-enemy.strength_total/strength_total) is correct formula
            //winners strength - ratio of losers strength to winners strength times winners strength

            // setting Nobles strength
            strength_total = (strength_total*(1-enemy.strength_total/strength_total));
            // make enemy noble dead and make each warrior in enemy to 0 strength
            enemy.set_strength(0);
            enemy.dead = true;
            // nobel total strength = 0
            enemy.strength_total = 0;
            
        }
        // if noble's strength is less than that enemy's strength
        else if (strength_total < enemy.strength_total){
            // print out message
            cout <<enemy.noble_name <<" defeats "<< noble_name<<endl;
            
            // call the set_strength method to set the enemy warriors' strength
            // based on specification
            enemy.set_strength(enemy.strength_total*(1-strength_total/enemy.strength_total));
            //(enemy.strength_total*(1-strength_total/enemy.strength_total)) is correct formula
            //winners strength - ratio of losers strength to winners strength times winners strength

            // set strength of enemy
            enemy.strength_total = (enemy.strength_total*(1-strength_total/enemy.strength_total));
            
            // set strength of warriors in noble to 0
            set_strength(0);
            // make nobel dead
            dead = true;
            strength_total = 0;
    }
    
    }
    // iterate through vector of pointers and set each Warriors strength to the value passed in
    void set_strength(double value){
        for (size_t i = 0; i<army.size(); i++){
            // derefrence address
            (army[i])->set_strength(value);
        }
    }
private:

    //private attibutes of the noble class
    string noble_name;
    double strength_total;
    
    // vector of pointrs to warrior types
    vector<Warrior*> army;
    bool dead;
};

int main() {
	// privided main!
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;
    lance.fire(nimoy);
    cout << lance << endl;
    
    
    cout << "==========\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
}

