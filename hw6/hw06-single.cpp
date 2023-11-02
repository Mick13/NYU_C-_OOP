/*
  hw06.cpp
  single file solution
  Mickey Shamah
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Noble foward declaration
class Noble;
// Class Warrior
class Warrior{
    
    //output operator prototype for Warrior
    friend ostream& operator << (ostream & os, const Warrior& warrior); 
public:

    // Warrior constructor prototype
    Warrior(const string& name, double strength);

    // Warrior method prototypes
    void hire(Noble* newBoss);
    const string& get_name() const;
    double get_strength() const;
    void set_strength(double value);
    void fire();
    bool isHired() const;
    void runaway();

    private:
//Defines the private member variables of the Warrior 
//class: name, strength, hired, dead, and boss.
    string name;
    double strength;
    Noble* boss;
};

// Class Warrior
class Noble {
    
    //output operator prototype for Noble
    friend ostream& operator << (ostream & os, const Noble& noble);
    
public:

    // Noble constructor prototype
    Noble(const string& noble_name);
 
    // Noble method prototypes
    const string& get_name() const;
    bool hire (Warrior& warrior) ;
    bool fire (Warrior& warrior);
    void battle (Noble& enemy);
    void set_strength(double value);
    bool removeWar(size_t wIndex);
    size_t findW (const Warrior& warrior) const;
private:

    //private attibutes of the noble class
    string noble_name;
    double strength_total;
    
    // vector of pointrs to warrior types
    vector<Warrior*> army;
    bool dead;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);
    
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha 
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha 
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}

// Warrior class constructor that initializes name,
// strength, hired status, dead status, and boss pointer
Warrior::Warrior(const string& name, double strength) : name(name),
 strength(strength), boss(nullptr) {}


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
    boss = newBoss;
    }
// Method to fire a Warrior from a Noble
void Warrior::fire() {
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
bool Warrior::isHired() const { return (boss != nullptr); }

// method to allow warrior to runaway from noble 
void Warrior::runaway(){

    // Check if the Warrior is not hired or is already dead
    if ((boss == nullptr) || !get_strength()){
        return;
        // If so, return without doing anything
    }
    // Print a message indicating that the Warrior is running away
    cout << name <<" flees in terror, abandoning his lord, " 
    << boss->get_name() <<endl;

    // Find the index of the Warrior in the boss's 
    //vector of warriors
    size_t index = boss->findW(*this);

     // Remove the Warrior from the boss's vector of warriors
    boss->removeWar(index);
    }


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
