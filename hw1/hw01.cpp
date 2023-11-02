#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
HW 1
Mickey Shamah
*/
//PROTOTYPES

char ceaser_char(char cur_char, int steps);
// Dont need ref because its a primative

void decrypt(string& scentence, int steps);


int main() {
    // checking if file "encrypted.txt" exists: if it doesnt exit
    ifstream encription("encrypted.txt");
    if (!encription){
      cerr << "Could not find encrypted.txt";
      exit(1);
    }

    // creating a string for the current scentence and a vector to hold scentences
    string line;
    vector<string> lines;
    int steps;

    // because the fist val in the file is the step value (int), push it onto a int: steps

    encription >> steps;


    // while the computer can read a line form the file
    // add to the end of a vector "lines"

    while (getline(encription, line)){
        lines.push_back(line);
    }
    encription.close();



    //cout << endl;

    //iterate through vector and call function decript for every scentence

    for (size_t i = 0; i < lines.size(); i++ ){
        decrypt (lines[i], steps);
        }

    // iterate backwords through vector and print each scentence
    for (size_t i = lines.size(); i > 0; i-- ){
        cout << lines[i-1] << endl;
      }



    }
// ceaser_char checks if char is uppercase. if it is it subtracts steps from it

char ceaser_char(char cur_char, int steps){
  // dont need CONST or & here becuase cur_char is a primative and it doesnt waste much space

    //assign cur chracter to decrypt_char, check if decrypt_char is captialized
    // if not dont modify
    //char decrypt_char = cur_char;
    if (cur_char >= 'A' && cur_char <= 'Z'){

      // if it is captialized rotate by  - steps and adjust
      // must concider the fact that it could wrap around ex A-1= Z
      cur_char  = (cur_char  - 'A' - steps +26 ) %26 +'A';
          }


    // return char
    return cur_char;


    }


// iterates through the string scentence and calls ceaser_char for every char

void decrypt(string& scentence, int steps) {
  // using & because you dont want to make a copy. you want to directly modify the string
  // no return type


  // iterating by index. use size_t b/c the for loop lenght is dependent on the size of the scentence

  for (size_t j = 0; j < scentence.size(); ++j) {
      scentence[j] = ceaser_char(scentence[j], steps);
         }

/*OR I can use this

  for (char& letter : scentence){
    letter = ceaser_char(letter, steps);
}

*/


    }
