#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

/*
    Mickey Shamah
    Noble.h
    HW 07
*/

namespace WarriorCraft {
    //Foward decleration
    class Protector;
    class Noble {
    // Overloaded output operator
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        Noble(const std::string& name);
        //pure virutal
        virtual void display(std::ostream& os) const = 0;

        //getters
        const std::string getName() const;
        virtual double getStrength() = 0;
        virtual void setStrength(double ratio) = 0;

        virtual void defend() = 0;
        void battle(Noble& enemy);
    // can only acces protected inside the class
    private:
    std::string name;
    bool dead;
        };
    //class Lord
    class Lord : public Noble {
    public:
    //constructor
        Lord(const std::string& name);

        //display method
        void display(std::ostream& os) const;

        //getters
        double getStrength();
        void setStrength(double ratio);

        void remove (size_t i);
        size_t findWarriorInd (const Protector& protector) const;

        // additional methods
        bool hires (Protector& protector);
        bool fires (Protector& protector);
        void defend();
    private:
        std::vector<Protector*> army;
        double strength;
    };

    
    class PersonWithStrengthToFight : public Noble {
    public:
    //constructor
    PersonWithStrengthToFight(const std::string& name, double istrength);
        void display(std::ostream& os) const;
        double getStrength();
        void setStrength(double value);
        void defend();
    private:
        double strength;
        };
}
#endif