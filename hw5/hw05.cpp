#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
Mickey Shamah
OOP hw05 */

// Class Warrior
class Warrior{
    
//defines the output operator as a friend of the class so it can access 
//the private attirbutes
    friend ostream & operator << (ostream & os, const Warrior& warrior){
        os << "\t" << warrior.name<<": " <<warrior.strength;
        return os;
    }  
// Declares that the following member functions and variables are accessible
// from outside the class.   
public:

    //Defines a constructor that takes a const reference to a string for 
    //the warrior's name,
    // and an integer for the warrior's strength. 
    Warrior(const string& name, double strength) : name(name),
    strength(strength), hired(false), dead(false){}
    
//Defines public member functions for the Warrior class:
// these functions either get or set private member variables of the 
//warrior class
// will be used in noble class
    bool employed() const {return hired;}
    bool death() const {return dead;}
    void hire() {hired = true;}
    const string& get_name() const {return name;}
    double get_strength() const {return strength;}
    void set_strength(double value) {
        // if the value is 0 make the Warrior dead!
        strength = value;
        if (value==0){
            dead = true;
        }
    }
    void fire() {hired = false;}
    void kill() {dead = true;}
    private:
//Defines the private member variables of the Warrior class: 
//name, strength, hired, and dead.
    string name;
    double strength;
    bool hired;
    bool dead;
};

// Class Warrior
class Noble {
    
    //defines the output operator as a friend of the Noble class so 
    //it can access the private attirbutes
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

    //Defines a constructor that takes a const reference to a string 
    //for the noble's name,
    // and an integer for the noble's strength. 
    Noble(const string& noble_name) : noble_name(noble_name), 
    strength_total(0), dead(false){}
 
    //public methods and attributes   
    //get name
    const string& get_name() const {return noble_name;}

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
                break;
            }      
        }
         // if the warrior is found in the army, fire the warrior 
        if (found == true){
            warrior.fire();
            // remove its strength form the total strength of the Noble
            strength_total -= warrior.get_strength();
            
            //output response
            cout <<warrior.get_name()<<", you don't work for me any more! -- "
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
            set_strength(1-(enemy.strength_total/strength_total));
            // based on specification
            //strength_total*(1-enemy.strength_total/strength_total) is correct formula
            //winners strength - ratio of losers strength to winners strength
            // times winners strength

            // setting Nobles strength
            strength_total = (strength_total*(1-(enemy.strength_total/strength_total)));
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
     void set_strength(double value){
        for (size_t i = 0; i<army.size(); i++){
            // derefrence address
            (army[i])->set_strength((army[i]->get_strength())*value);
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

// A function to find a warrior with a given 
//name from a vector of Warrior pointers
size_t find_Warrior(const vector <Warrior*>& war, const string& name);

// A function to find a noble with a given name 
//from a vector of Noble pointers
size_t find_Noble(const vector <Noble*>& war, const string& name);

// A function to create and add a new Noble object 
//to the vector of Noble pointers
void assign_noble(vector <Noble*>& noble, const string& name);

// A function to create and add a new Warrior object
// to the vector of Warrior pointers
void assign_warrior(vector <Warrior*>& war, const string& name, int strength);

// A function that calls the hire method on a noble object
// objects must be derefrenced
void hire(const string& boss_Noble,const string &employee_Warrior, 
    vector <Warrior*>& war, vector <Noble*>& noble);

// A function to print the status of all the Nobles and Warriors
void status(const vector <Warrior*>& war,const vector <Noble*>& noble);

// A function that calls the fire method on a noble object
// objects must be derefrenced
void fire(const string& boss_Noble,const string &employee_Warrior, 
    const vector <Warrior*>& war, const vector <Noble*>& noble);

// A function to initiate a battle between two 
//Noble objects with given names
void battle(vector <Noble*>& noble, const string &noble_1, const string& 
noble_2);
    
// A function to delete all the Warrior and Noble objects from their vectors
// set their pointers to null
void clear (vector <Warrior*>& war, vector <Noble*>& noble);

// Main function for running the program
int main(){

    // Open input file
    ifstream file("nobleWarriors.txt");

    // Check if the file exists
    if (!file){
      cerr << "Couldnt Find warriors.txt";
      exit (1);
    }
    
    // Initialize variables
    string command;
    vector <Warrior*> war;
    vector <Noble*> noble;

    // Loop through file and execute commands based on input
    while (file >> command){

        // If the command is to create a Noble
        //call assign_noble function
        if (command == "Noble"){
            string name;
            file >> name;
            assign_noble(noble, name);     
        }

        // If the command is to create a Warrior
        //call assign_warrior function
        else if (command == "Warrior"){
            string name;
            int strength;
            file >> name >> strength;
            assign_warrior(war, name, strength);
        }

        // If the command is to hire a Warrior to a Noble
        //call hire function
        else if (command == "Hire"){
            string boss_Noble;
            string employee_Warrior;
            file >> boss_Noble >> employee_Warrior;
            hire(boss_Noble, employee_Warrior, war, noble);  
        }

        // If the command is to display the current status 
        //of all Nobles and Warriors
        // call status function
        else if (command == "Status"){
            status(war, noble);
        }

        // If the command is to fire a Warrior from a Noble
        // call fire function
        else if (command == "Fire"){
            string boss_Noble;
            string employee_Warrior;
            file >> boss_Noble >> employee_Warrior;
            fire(boss_Noble, employee_Warrior, war, noble);
        }

        // If the command is to initiate a battle between two Nobles
        // call battle function
        else if (command == "Battle"){
            string noble_1;
            string noble_2;
            file >> noble_1 >> noble_2;
            battle(noble, noble_1, noble_2);
        }

        // If the command is to clear all Nobles and Warriors
        // call clear function
        else if (command == "Clear"){
            clear (war, noble);    
        }   
    }
    file.close();
}


size_t find_Warrior(const vector <Warrior*>& war, const string& name){
    // searches for a Warrior object in the provided vector of Warrior pointers 
    for (size_t i = 0; i< war.size(); i++){
        if (war[i]->get_name() == name){
            // derefrences the warrior and calls the get_name method on it
            return i;
            //if that == the name return the index
        }
    }
    //else return the size of the vector
    return war.size();
}

size_t find_Noble(const vector <Noble*>& war, const string& name){
    // searches for a Noble object in the provided vector of Noble pointers 
    for (size_t i = 0; i< war.size(); i++){
        if (war[i]->get_name() == name){
             // derefrences the Noble and calls the get_name method on it
            return i;
             //if that == the name return the index
        }
    }
    //else return the size of the vector
    return war.size();
}

void assign_noble(vector <Noble*>& noble, const string& name){
    // Check if noble already exists in the vector
    if (find_Noble(noble, name) == noble.size()){
        // If noble doesn't exist, 
        //create a new noble and push it to the vector
        Noble* new_noble = new Noble(name);
        noble.push_back(new_noble);
    }
    else{
        // If noble already exists, print an error message
        cout <<name<< " already exists!"<<endl;
    }

    return;
}

void assign_warrior(vector <Warrior*>& war, const string& name, int strength){
    // Check if warrior already exists in the vector
    if (find_Warrior(war, name) == war.size()){
        // If warrior doesn't exist, create a new warrior and push it to the vector
        Warrior* new_warrior = new Warrior(name, strength);
        war.push_back(new_warrior);
    }
    else{
        // If warrior already exists, print an error message
        cout <<name<< " already exists!"<<endl;
    }

    return;
}


void hire(const string& boss_Noble,const string &employee_Warrior, 
    vector <Warrior*>& war, vector <Noble*>& noble){
    // Find the indices of the nobles and the warrior in both vectors
    size_t n_index = find_Noble(noble, boss_Noble);
    size_t w_index = find_Warrior(war, employee_Warrior);

    // Check if n_index was found in the vector,
    // if not print error message and return
    if (n_index == noble.size()){
        cout <<"Attempting to hire using unknown warrior: "<<boss_Noble<<endl;
        return;
    }

    // Check if w_index was found in the vector,
    // if not print error message and return
    if (w_index == war.size()){
         cout <<"Attempting to hire using unknown noble: "<<employee_Warrior<<endl;
        return;
    }

    // call the hire between method on a noble and a warrior
    // derefrence the noble and warrior objects
    noble[n_index]->hire(*war[w_index]);

}

void status(const vector <Warrior*>& war,const vector <Noble*>& noble){
    // This function prints the status of the warriors and nobles
    int count = 0;       
    cout << "Status\n"<<"======\n"<<"Nobles:\n";

     // Check if there are any nobles
    if (noble.size() == 0){
        cout <<"NONE"<<endl;
    }
    else{
         // Print all nobles
        for (size_t i = 0; i<noble.size();i++){
        cout << *(noble[i])<<endl;
            }
    }
    cout << "\nUnemployed Warriors:\n";
    // Print all unemployed warriors
    for (size_t i = 0; i<war.size();i++){
    if (war[i]->employed() == false){
         count +=1;
         cout << *(war[i]); 
    }
}
    // Check if there are any unemployed warriors
    if (count==0){
        cout<<"NONE"<<endl;
                }
    else{
        cout<<endl;
    }
            
        }
//why is vector const
void fire(const string& boss_Noble,const string &employee_Warrior, 
     const vector <Warrior*>& war, const vector <Noble*>& noble){
    // Find the indices of the nobles and the warrior in both vectors
    size_t n_index = find_Noble(noble, boss_Noble);
    size_t w_index = find_Warrior(war, employee_Warrior);

    // Check if n_index was found in the vector, 
    //if not print error message and return
    if (n_index == noble.size()){
        cout <<"Attempting to fire using unknown warrior: "<<boss_Noble<<endl;
        return;
    }
    // Check if w_index was found in the vector, 
    //if not print error message and return
    if (w_index == war.size()){
         cout <<"Attempting to fire using unknown noble: "<<employee_Warrior<<endl;
        return;
    }

    // call the fire between method on a noble and a warrior
    // derefrence the noble and warrior objects
    noble[n_index]->fire(*war[w_index]);
    //Fire King_Arthur Tarzan
    }

void battle(vector <Noble*>& noble, const string &noble_1,
 const string& noble_2){
    // Find the indices of the two nobles in the vector
    size_t n1_index = find_Noble(noble, noble_1);
    size_t n2_index = find_Noble(noble, noble_2);

    // Check if noble_1 was found in the vector, 
    //if not print error message and return
    if (n1_index == noble.size()){
        cout <<"Attempting to battle using unknown noble: "<<noble_1<<endl;
        return;
    }
     // Check if noble_2 was found in the vector,
     // if not print error message and return
    if (n2_index == noble.size()){

        cout <<"Attempting to battle using unknown noble: "<<noble_2<<endl;
        return;
    }
    // Initiate the battle between the two found nobles
    // derefrence the both noble objects
    noble[n1_index]->battle(*noble[n2_index]);
}

void clear (vector <Warrior*>& war, vector <Noble*>& noble){

    // Loop through all elements in the war vector
    for (size_t i = 0; i<war.size();i++){
        // Delete each warrior object being pointed to in the vector
        delete war[i];
        // Set the vector element (a pointer) to null
        war[i] = nullptr;
    }
    // Loop through all elements in the noble vector
    for (size_t i = 0; i<noble.size();i++){
        // Delete each noble object being pointed to in the vector
        delete noble[i];
       // Set the vector element (a pointer) to null
        noble[i] = nullptr;
    }
    // Clear both vectors
    war.clear();
    noble.clear();
}
