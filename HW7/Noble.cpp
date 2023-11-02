/*
  hw07.cpp
  Noble.cpp
  Mickey Shamah
 */

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;


namespace WarriorCraft {

    // Noble class constructor
    Noble::Noble(const string& name) : name(name), dead(false) {};

    // Function to get the name of the noble
    const string Noble::getName() const {return name;};
    // Function to simulate a battle between two nobles

    // PROBLEM WAS I WAS SETING THE LOOSERS RATIO TO BUT IT HAD TO BE ONE
    void Noble::battle(Noble& enemy) {
        //Retriving the current strength of Noble and enemy

        // Had issues with this previously
        double strength = getStrength();
        double enemy_strength = enemy.getStrength();

        cout<<name<<" battles "<<enemy.name<<endl;
        if (dead && enemy.dead) {
            // If they are both dead display error message
            cout<<"Oh, no! They're both dead! Yuck!"<<endl;
            }
        // if one is dead display thry error message and call the defend method
        // for the one that has a nonzero strength
        else if (dead == true) {
            
            enemy.defend();
            cout<<"He's dead, "<<enemy.name<<endl;
        }
        else if (enemy.dead == true) {
            defend();
            cout<<"He's dead, "<<name<<endl;
            }
        else if (strength == enemy_strength) {
                defend();
                enemy.defend();
                cout<<"Mutual Annihilation: "<<name<<" and " 
                <<enemy.name<<" die at each other's hands"<<endl;
                dead = true;
                enemy.dead = true;
                //set strength og both enemy and noble to 0
                setStrength(1);
                enemy.setStrength(1);

        }
    // Checking if this noble has greater strength
    else if (strength > enemy_strength) {
        defend();
        enemy.defend();

        cout<<name<<" defeats "<<enemy.name<<endl;
        enemy.dead = true; 
        // Setting the enemy noble's dead vlaue to true

        enemy.setStrength(1); 
        // Setting the enemy noble's strength to 0
        double ratio = enemy_strength/strength; 
        setStrength(ratio); 
        // Setting the strength of this noble's army based on the ratio
        }
    // Checking if the enemy noble has greater strength




    else if (strength < enemy_strength) {
        defend();
        enemy.defend();
        cout<<enemy.name<<" defeats "<<name<<endl;

        dead = true; 
        // Setting this noble's dead value to true
        setStrength(1);
        double ratio = strength/enemy_strength; 
        enemy.setStrength(ratio); 
        // Setting the strength of the enemy noble's army based on the ratio
        }
    // Updating the strength values of both nobles
    getStrength();
    enemy.getStrength();
    }



    ostream& operator<<(ostream& os, const Noble& rhs) {
        rhs.display(os);
        return os;
}

    // Constructor for PersonWithStrengthToFight
    PersonWithStrengthToFight::PersonWithStrengthToFight
    (const string& iname, double istrength) : 
    Noble(iname), strength(istrength) {};

    // Display function for PersonWithStrengthToFight
    void PersonWithStrengthToFight::display(ostream& os) const {
    os << name << " has strength: " << strength;
    }

   
    // Getter function for strength of PersonWithStrengthToFight 
    double PersonWithStrengthToFight::getStrength() 
        {return strength;}

    // Setter function for strength of PersonWithStrengthToFight
    void PersonWithStrengthToFight::setStrength(double value) 
        {strength -= (strength*value);};

    // Defend function for PersonWithStrengthToFight
    //always going to output "UGH!"
    void PersonWithStrengthToFight::defend() 
        {cout << "Ugh!" << endl;};


    //Lord constructor
    Lord::Lord(const string& name) : Noble(name) {};

    // Lord display operator
    void Lord::display(ostream& os) const {
    os << name << " has an army of size: " << army.size() << endl;
    for (const Protector* protector : army) {
        os << '\t' << *protector << endl;
    }
    }
    // Getter function for strength of Lord
    double Lord::getStrength() {
    strength = 0;
    for(const Protector* fighter : army) {
        strength += fighter->getStrength();
    }
    return strength;
    }
    // Setter function for strength attribute of Lord
    void Lord::setStrength(double ratio) {
    for(Protector* protector : army) {
        protector->setStrength(ratio);
    }
    getStrength();
    }
    // Remove function to remove an protector from Lords army
    void Lord::remove (size_t i) {
    while (i < army.size()-1) {
        army[i] = army[i+1];
        i+=1;
    }
    army.pop_back();
    };

    // Iterates through army to find warrior index
    size_t Lord::findWarriorInd (const Protector& protector) const {
    size_t i = 0;
    for (const Protector* fighter : army) {
        if(&protector == fighter) {
            return i;
        };
        ++i;
    }
    return army.size();
    }

    // Lord Hires method to add a protector to the army
    bool Lord::hires (Protector& rhs) {
    if(rhs.getStatus() || dead) {
            cout<<name<<" failed to hire "<<rhs.getName()<<endl;
            return false;
    }
    else {
            army.push_back(&rhs);

            rhs.set_boss(this);
            return true;
    }
    };

    // Lord Fires method to remove a protector from the army
    bool Lord::fires (Protector& someone) {
    if(findWarriorInd(someone)==army.size() || dead) {
        cout<<name<<" failed to fire "<<someone.getName()<<endl;
        return false;
    }
    else {
        cout<<someone.getName()<<", you don't work for me any more! -- "
        <<name<<endl;
        remove(findWarriorInd(someone));
        someone.set_boss(nullptr);
        return true;
    }
    };
    // calling the defend method of each protector
    void Lord::defend() {
    for (Protector* someone : army){
        if(strength != 0) {
        someone->fight();
        cout << endl; 
        }
    }
    }




}