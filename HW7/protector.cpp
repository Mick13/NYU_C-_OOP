#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;

/*
    Mickey Shamah
    Protector.cpp
    HW 07
*/

namespace WarriorCraft {

    // Constructor for Protector class
    Protector::Protector(const string& name, int istrength) : name(name), strength(istrength), boss(nullptr) {};

    // getter - returns strength of protector
    double Protector::getStrength() const {return strength;};

    // getter - returns name of protector
    const string Protector::getName() const {return name;};

    // getter - returns status of protector's boss
    // true if it has a boss and false if it doesnt
    bool Protector::getStatus() const {return boss;};

    // Sets protector's boss to Lord object
    void Protector::set_boss(Lord* someone) {boss = someone;};

    // Reduces protector's strength by given ratio
    void Protector::setStrength(double dmg) {strength -= (strength*dmg);};

    // Checks if protector has a boss, 
    //if yes makes the protector runaway 
    // remove it from its boss's army
    bool Protector::runaway() {
    if (boss) {
        cout << name << " flees in terror, abandoning his lord, " <<
         boss->getName() << endl;
        boss->remove(boss->findWarriorInd(*this));
        boss = nullptr;
        return true;
    }
    else {
        return false;
    }
    }

    // Overloaded operator to output Protector object
    ostream& operator<<(ostream& os, const Protector& rhs) {
    os << rhs.name << " has strength " << rhs.strength;
    return os;
    };

    // Constructor for Wizard class, 
    //inherits from Protector class
    Wizard::Wizard(const string& name, int istrength) : 
    Protector(name,istrength) {};

    // Overrides fight method of Protector class
    void Wizard::fight() {cout<<"POOF";};

    // Constructor for Warrior class, 
    //inherits from Protector class
    Warrior::Warrior(const string& name, int istrength) :
     Protector(name,istrength) {};

    // Overrides fight method of Protector class
    void Warrior::fight() {
    cout<<" says: Take that in the name of my lord, ";
    }

    // Constructor for Archer class, 
    //inherits from Warrior class
    Archer::Archer(const string& name, int istrength) :
     Warrior(name,istrength) {};

    // Overrides fight method of Warrior class
    void Archer::fight() {
    cout<<"TWANG! " << name;
    Warrior::fight(); 
    cout << boss->getName();
    };

    // Constructor for Swordsman class,
    // inherits from Warrior class
    Swordsman::Swordsman(const string& name, int istrength) :
     Warrior(name,istrength) {};

    // Overrides fight method of Warrior class
    void Swordsman::fight() {
    cout<<"CLANG! " << name;
    Warrior::fight();
    cout << boss->getName();
    };
}
