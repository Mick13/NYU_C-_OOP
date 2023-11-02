// rec13_start.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;


// FILE READ P1

void count_word(const string& f_name){
    ifstream file (f_name);
    vector<string> v;
    string word;
    while (file >> word){
        if (find(v.begin(), v.end(), word) ==  v.end()){
            v.push_back(word);
        }
    }
    cout<<"length of vector: "<<v.size()<<endl;;
    for (const string& str : v){
        cout<<str<<" ";
    }
    file.close();
}


void map_count_word(const string& f_name){
    ifstream file (f_name);
    map<string, vector<int>> wordMap;
    int pos = 0;
    string word;
    while (file >> word){
        pos+=1;
        wordMap[word].push_back(pos);
    }
    cout<<"length of vector: "<<wordMap.size()<<endl;;
    for (const auto& pair : wordMap){
        cout<<pair.first<<"positions: ";
        for (auto val : pair.second){
            cout<<val<<" ";
        }
        cout<<endl;
    }
    
    file.close();
}



void set_count_word(const string& f_name){
    ifstream file (f_name);
    set<string> s;
    string word;
    while (file >> word){
        s.insert(word);
    }
    cout<<"length of vector: "<<s.size()<<endl;;
    for (const string& str : s){
        cout<<str<<" ";
    }
    file.close();
}



template<typename fred, typename q>
fred ourFind(fred begin, fred end, q target){
    cout<<"TEMPLATE"<<endl;
        for(fred p = begin; p != end; ++p){
            if (*p == target){
                return p;
            }
            
        }
        return end;

}


list<int>::const_iterator ourFind(list<int>::const_iterator 
begin ,list<int>::const_iterator end, int val){
        for(auto iter = begin; iter!=end; ++iter){
            if (*iter == val){
                return iter;
            }
            
        }
        return end;

}




class even_{
public:
    bool operator() (int x) const {return x%2 == 0;}
};


bool even (int x) {return x%2 == 0;}

list<int>::const_iterator find_List(const list<int>& l1, int val){
        for(list<int>::const_iterator iter = l1.begin(); iter!=l1.end(); ++iter){
            if (*iter == val){
                return iter;
            }
            
        }
        return l1.end();




}

list<int>::const_iterator usingAuto_find_List(const list<int>& l1, int val){
        for(auto iter = l1.begin(); iter!=l1.end(); ++iter){
            if (*iter == val){
                return iter;
            }
            
        }
        return l1.end();
}
void printvec_int (const vector<int>& v1){
    for (int val : v1){
        cout<<val<<" ";
    }
}

void print_list(const list<int>& l1){
    for(list<int>::const_iterator iter = l1.begin(); iter!=l1.end(); ++iter)
        cout<<(*iter);
}

void print_list_rf(const list<int>& l1){
    for(int data : l1)
        cout<<(data);
}


void print_list_auto(const list<int>& l1){
    for(auto iter = l1.begin(); iter!=l1.end(); ++iter)
        cout<<(*iter);
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v1{9,4,2,1,3, 6};
    printvec_int(v1);
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l1(v1.begin(), v1.end());

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v1.begin(), v1.end());
    printvec_int(v1);
    cout<<endl;
    for (int val : l1){
        cout<<val<<" ";
    }


    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    
    for (size_t i = 0; i <v1.size(); i+=2){
        cout<<v1[i]<<" ";
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for (size_t i = 0; i <l1.size(); i+=2){
    //     cout<<l1[i]<<" ";
    // }


    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for (vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter+=2){
        cout<<(*iter)<< " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter = l1.begin(); iter != l1.end(); ++iter, ++iter){
        cout<<(*iter)<< " ";
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    
    //sort(l1.begin(), l1.end());
    l1.sort();
    for (const int& val : l1){
        cout<<val<<" ";
    }
    
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
     print_list(l1);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";

    print_list_rf(l1);
    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_list_auto(l1);

    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout<<*(find_List(l1,2))<< " ";
    //cout<<*(find_List(l1,5));
    

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
   
    cout << "Task 13:\n";
    cout<<*(find_List(l1,2))<< " ";

    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout<<*find(l1.begin(), l1.end(),2);
    
    cout<<endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";

    cout<<*find_if(v1.begin(),v1.end(), even);
    cout<<endl;
    cout<<*find_if(l1.begin(),l1.end(), even);

    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    even_ obj;
    cout<<*find_if(l1.begin(),l1.end(), obj);
    cout << "\n =======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    //[] { cout << "Hello Lambda!"; }();

    cout<<*find_if(l1.begin(),l1.end(), [](int x){return x % 2 ==0;});
    cout << "\n =======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* d_arr  = new int[6];
    copy(l1.begin(), l1.end(), d_arr);
    for (size_t i = 0; i < 6; i++){
        cout<<d_arr[i]<<" ";
    }
    delete [] d_arr;
    cout << "\n======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";

    cout<<*ourFind(l1.begin(),l1.end(), 3);
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    count_word("pooh-nopunc.txt");
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";  
    
    set_count_word("pooh-nopunc.txt");
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";

    map_count_word("pooh-nopunc.txt");
    cout << "=======\n";
}
