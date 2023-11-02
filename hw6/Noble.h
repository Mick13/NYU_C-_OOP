//Noble.h
#include <iostream>
#include <string>
#include <vector>

#ifndef Noble_H
#define Noble_H

namespace WarriorCraft{
    class Warrior;
    class Noble {
        
        //output operator prototype for Noble
        friend std::ostream& operator << (
            std::ostream & os, const Noble& noble);
        
    public:

        // Noble constructor prototype
        Noble(const std::string& noble_name);
    
        // Noble method prototypes
        const std::string& get_name() const;
        bool hire (Warrior& warrior) ;
        bool fire (Warrior& warrior);
        void battle (Noble& enemy);
        void set_strength(double value);
        bool removeWar(size_t wIndex);
        size_t findW (const Warrior& warrior) const;
    private:

        //private attibutes of the noble class
        std::string noble_name;
        double strength_total;
        
        // vector of pointrs to warrior types
        std::vector<Warrior*> army;
        bool dead;
    };




}

#endif