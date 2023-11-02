#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
    Mickey Shamah
    Protector.h
    HW 07
*/

namespace WarriorCraft {
    class Lord; 
    // Forward declaration of Lord class

    // Base class for different types of protectors
class Protector {
  friend std::ostream& operator<<(std::ostream& os, 
  const Protector& rhs);
  // Declare friend operator to output Protector object
public:
//constructor
  Protector(const std::string& name, int strength);

  //methods
  double getStrength() const;
  const std::string getName() const;
  bool getStatus() const;
  void set_boss(Lord* someone);
  void setStrength(double dmg);
  bool runaway();
  //pure virtual
  virtual void fight() = 0;


private:
  std::string name;
  double strength;
  Lord* boss;

};
 // Derived class for Wizard protector
class Wizard : public Protector {
public:
  Wizard(const std::string& name, int istrength);
  void fight();
};
// Derived class for Warrior protector
class Warrior : public Protector {
public:
  Warrior(const std::string& name, int istrength);
  virtual void fight() = 0;
};
// Derived class for Archer warrior
class Archer : public Warrior {
public:
  Archer(const std::string& name, int istrength);
  void fight();
};
// Derived class for Swordsman warrior
class Swordsman : public Warrior {
public:
  Swordsman(const std::string& name, int istrength);
  void fight();
};

}
#endif
