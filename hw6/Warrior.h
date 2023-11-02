//Warrior.h
#include <iostream>
#include <string>
#include <vector>

#ifndef Warrior_H
#define Warrior_H


namespace WarriorCraft{
    class Noble;
    class Warrior{
        
        //output operator prototype for Warrior
        friend std::ostream& operator << 
        (std::ostream & os, const Warrior& warrior); 
    public:

        // Warrior constructor prototype
        Warrior(const std::string& name, double strength);

        // Warrior method prototypes
        void hire(Noble* newBoss);
        const std::string& get_name() const;
        double get_strength() const;
        void set_strength(double value);
        void fire();
        bool isHired() const;
        void runaway();

        private:
    //Defines the private member variables of the Warrior 
    //class: name, strength, hired, dead, and boss.
        std::string name;
        double strength;
        bool hired;
        Noble* boss;
    };


}

#endif