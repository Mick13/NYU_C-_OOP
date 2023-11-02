/*
  rec14 Mickey Shamah 
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    int data;
    Node* next;
};

// Node type for the binary tree
struct TNode {
  int data;
  TNode *left, *right;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function:
Node* listSum(const Node* rhs, const Node* lhs){
    if (rhs == nullptr && lhs==nullptr) return nullptr;
    if (rhs == nullptr) {
        return new Node{lhs->data , listSum(rhs, lhs->next)};
    }
    if (lhs == nullptr) {
        return new Node{rhs->data , listSum(rhs->next, lhs)};
    }
    return new Node{lhs->data + rhs->data , listSum(rhs->next, lhs->next)};

}

//   Task 2 function:


int treeMax(const TNode* T){
    //try{}
    if (T == nullptr){
        throw invalid_argument("ERROR");
    }
    //
    int curr_max = T->data;
    
    if (T->right != nullptr){
        curr_max =  std::max(curr_max, treeMax(T->right));
    }
    if (T->left != nullptr){
        curr_max =  std::max(curr_max, treeMax(T->left));
    }
    
    return curr_max;
    
}
//   Task 3 function:
bool palindrome(const char* word , int length){
    if (length <2) return true;
    if( *word != *(word+length-1)){
        return false;
    }
    return palindrome(word+1, length-2);
    
}
//   Task 4 function:
bool parity(unsigned val) {
    if (val <2) {
        return val;
    }
    else{
        if (parity(val/2)){
            return !(val%2);
        }
        else{
            return (val%2);
        }
    } 
}


//   Task 5 function:
int towers(int size, char start, char target, char spare){
    if (size == 0) return size;
    return ( towers( size-1, start, spare, target)+ towers( size-1, spare, target, start)+1);
    
    
}

void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}


int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


     cout << "\n==============\n#2: \n";
    // Task 2:
    TNode a{1}, b{2}, c{4}, d{8, &a, &b}, e{16, &c}, f{32, &d, &e};
    cout << treeMax(&f) << endl;

    try{
        cout << treeMax(nullptr) << endl;
    }
    catch (invalid_argument ex){
        cerr << "invalid_argument: " << ex.what() << endl;
    }
    

    
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
	 << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;

    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    
    // Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


    
    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): " 
	     << towers(i, 'a', 'b', 'c') << endl;
    }

    mystery(10);

    
}


//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
}
