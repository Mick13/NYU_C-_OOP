//Noble.cpp
#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft{

// Noble constructor
Noble::Noble(const string& noble_name) : noble_name(noble_name), 
strength_total(0), dead(false){}


// Overloaded << operator to print Noble information
ostream & operator << (ostream & os, const Noble& noble){
    os << noble.noble_name << " has an army of "
    <<noble.army.size() <<endl;
    for (size_t i = 0; i<noble.army.size(); i++){
        os<<*(noble.army[i]) << " \n"[i != noble.army.size() - 1];
        
    }
    return os;
}


// get name


const string& Noble::get_name() const{
    return noble_name;
}
// Noble hire method

// Do not pass by const!
bool Noble::hire (Warrior& warrior){
    // Check if the noble is dead
    if (dead == true){
        cout << noble_name<< " failed to hire "
        <<warrior.get_name()<<endl;
        return false;
    }
    
    
    else if (warrior.isHired() == false && warrior.get_strength() != 0){
        // add the address of the warrior to the army
        army.push_back(&warrior);
        //make "this" the warriors boss
        //modify warrior
        warrior.hire(this);


        // update total strength
        strength_total += warrior.get_strength();
        return true;
    }
    else{
        // If the warrior is already hired by another 
        //noble return false
        cout << noble_name<< " failed to hire "<<
        warrior.get_name()<<endl;
        return false;
    }
}

bool Noble::fire (Warrior& warrior){
    // Check if the noble is dead
    // Check if the Warrior is dead
    if (!warrior.get_strength() || dead){
        cout << noble_name<< " failed to fire "
        <<warrior.get_name()
        <<endl;
        return false;
    }

// call the revove warrior on the index of the warrior
// found by the findW method
// found will ony be true if wIndex >= army.size()

    bool found = removeWar(findW(warrior));
    
    if (found == true){
    //output response
        cout <<warrior.get_name()<<", you don't work for me any more! -- "
            <<noble_name<<"."<<endl;  
            return true;
        }
        
    // If the warrior is not found in the army, return false
    cout << noble_name<< " failed to fire "<<warrior.get_name()<<endl;
    return false;
}

//method to find warrior index in army
size_t Noble::findW(const Warrior& warrior) const{
    // iterate through army
    for(size_t i = 0; i<army.size(); i++)
    // if found return index
        if (army[i] ==  &warrior){
            return i;
        }
        // return size pf army
        return army.size();
    }


// This method removes a warrior from the noble's army
bool Noble::removeWar(size_t wIndex) {
// If wIndex is greater than or equal to the size of the army,
// then the warrior was not found
    if (wIndex >= army.size()) {
    return false;
    }
// Store the removed warrior and fire it
    Warrior* removed_warrior = army[wIndex];
// the fire sets its boss to nullptr and its status to unemployed
    (removed_warrior)->fire();

// Subtract the removed warrior's strength from the noble's total strength
    strength_total -= (removed_warrior)->get_strength();

// Replace the removed warrior with nullptr
// and shift all warriors by one spot
    army[wIndex] = nullptr;
    for (size_t j = wIndex; j < army.size() - 1; j++){
        army[j] = army[j+1];
            }

// Pop the last warrior in the army vector
// (which is now nullptr)
    army.pop_back();

    return true;
        }

//noble battle method
void Noble::battle (Noble& enemy){
    
    // print the name of the nobles in battle
    cout << noble_name<< " battles " << enemy.noble_name <<endl;
    
    // if both already dead print out
    if (dead == true && enemy.dead == true){
        cout <<"Oh, NO!  They're both dead!  Yuck!"<<endl;
    }
    // If this noble is already dead and the enemy 
    //noble is stronger print message
    else if  (strength_total < enemy.strength_total && dead == true ){
        cout <<"He's dead, " << enemy.noble_name<<endl;
    }
    
    // If the enemy noble is already dead and this
    // noble is stronger print message
    else if (strength_total > enemy.strength_total && enemy.dead== true ){
        cout <<"He's dead, " << noble_name<<endl;
    }
    
    // If both nobles have equal strength, they kill each other
    else if (strength_total == enemy.strength_total){
        cout <<"Mutual Annihilation: "<<noble_name <<" and "<<
            enemy.noble_name<<" die at each other's hands"<<endl;
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
        set_strength(1-(enemy.strength_total/strength_total));
        // based on specification
        //strength_total*(1-enemy.strength_total/strength_total)
        // is correct formula
        //winners strength - ratio of losers strength to winners strength
        // times winners strength
        // setting Nobles strength
        strength_total = (strength_total*(1-
        (enemy.strength_total/strength_total)));
        // make enemy noble dead and make each warrior 
        //in enemy to 0 strength
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
        enemy.set_strength((1-strength_total/enemy.strength_total));
        //winners strength - ratio of losers strength to winners strength
        // times winners strength

        // set strength of enemy
        enemy.strength_total = (enemy.strength_total*
        (1-strength_total/enemy.strength_total));
        
        // set strength of warriors in noble to 0
        set_strength(0);
        // make nobel dead
        dead = true;
        strength_total = 0;
        }   
}
// iterate through vector of pointers and set each 
//Warriors strength to the value passed in
void Noble::set_strength(double value){
    for (size_t i = 0; i<army.size(); i++){
        // derefrence address
        (army[i])->set_strength((army[i]->get_strength())*value);
    }
}
}