//Warrior.cpp
#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft{


// Warrior class constructor that initializes name,
// strength, hired status, dead status, and boss pointer
Warrior::Warrior(const string& name, double strength) : name(name),
 strength(strength), hired(false), boss(nullptr) {}


// Overloaded << operator to print Warrior information
ostream & operator << (ostream & os, const Warrior& warrior){
    os << "\t" << warrior.name<<": " <<warrior.strength;

    // return ostream
    return os;
}  

// Method to check if Warrior is dead

// Method to hire a Warrior to a Noble
void Warrior::hire(Noble* newBoss) {
    // sets the warrior's boss to the noble passed in
    // not const
    hired = true;
    boss = newBoss;
    }
// Method to fire a Warrior from a Noble
void Warrior::fire() {
    hired = false;
    boss = nullptr;
}
// Method to get the name of a Warrior
const string& Warrior::get_name() const {return name;}

// Method to get the strength of a Warrior
double Warrior::get_strength() const {return strength;}
    
// Method to set the strength of a Warrior and check if
// they are dead
void Warrior::set_strength(double value) {
        // if the value is 0 make the Warrior dead!
        strength = value;
    }

// getter method to return if warrior is hired
bool Warrior::isHired() const { return hired; }

// method to allow warrior to runaway from noble 
void Warrior::runaway(){

    // Check if the Warrior is not hired or is already dead
    if (!hired || !get_strength()){
        return;
        // If so, return without doing anything
    }
    // Print a message indicating that the Warrior is running away
    cout << name <<" flees in terror, abandoning his lord, " << 
    boss->get_name() <<endl;

    // Find the index of the Warrior in the boss's 
    //vector of warriors
    size_t index = boss->findW(*this);

     // Remove the Warrior from the boss's vector of warriors
    boss->removeWar(index);
    }

}