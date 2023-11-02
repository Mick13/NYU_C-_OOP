#include "polynomial.h"
using namespace std;

namespace Poly{

    //output operator
    ostream& operator<<(std::ostream& os, const Polynomial& rhs) {
        //qualify node
        Polynomial::Node* temp;
        temp = rhs.head_ptr;
        int count = rhs.degree;
        while (count > 0) {
            if (temp->data != 0) {
                if (temp->data == 1) {
                    os << "x";
                } else if (temp->data == -1) {
                    os << "-x";
                } else {
                    os << temp->data << "x";
                }
                if (count != 1) {
                    os << "^" << count;
                }
                os << " + ";
            }
            count -= 1;
            temp = temp->next;
        }
        os << temp->data;
        return os;
    }
    //defult constructor
    Polynomial::Polynomial() : head_ptr(nullptr), degree(0) {
        head_ptr = new Node();
    }
    //constructor given a vector of ints
    Polynomial::Polynomial(const vector<int>& coeffients ) : 
    degree(coeffients.size()-1), head_ptr(nullptr) {
            Node* temp_ptr = new Node();
            for (size_t i = 0; i < coeffients.size(); i ++){
                
                if (i == 0){
                    temp_ptr->data = coeffients[0];
                    head_ptr = temp_ptr;
                }
                else{
                    Node* val = new Node(coeffients[i]);   
                    temp_ptr->next = val;
                    temp_ptr = temp_ptr->next;
                }
            }
        }
    //destructor
    Polynomial::~Polynomial( ){
        while (head_ptr != nullptr){
            Node* temp = head_ptr->next;
            delete head_ptr;
            //not nessecary to make nullptr but good habit
            head_ptr = nullptr;
            head_ptr = temp;}
    }


    //Copy Constructor
    Polynomial::Polynomial(const Polynomial& rhs) :
             degree(rhs.degree), head_ptr(nullptr) {
        Node* temp = nullptr;
        Node* rhs_temp = rhs.head_ptr;
        while (rhs_temp != nullptr) {
            if (temp == nullptr) {
                temp = new Node{rhs_temp->data};
                head_ptr = temp;
            } else {
                temp->next = new Node{rhs_temp->data};
                temp = temp->next;
            }
            rhs_temp = rhs_temp->next;
           }
        }

    //Assigment operator
    Polynomial& Polynomial::operator = (const Polynomial& rhs){
        if (this != &rhs){
            degree =rhs.degree;
            Node* temp;
            while (head_ptr != nullptr){
                temp = head_ptr->next;
                delete head_ptr;
                head_ptr = nullptr;
                head_ptr = temp;

            }
            temp = nullptr;
            Node* rhs_temp = rhs.head_ptr;

            while (rhs_temp != nullptr) {
                if (temp ==nullptr){
                    temp = new Node{rhs_temp->data};
                    head_ptr = temp;  
                }
                else{
                    temp->next =  new Node{rhs_temp->data};
                    temp = temp->next;
                }
                rhs_temp = rhs_temp->next;
            }
        }
        return *this;
    }

    //equality operator
    //returns a bool
    bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
        // implment as a function
        // must qualify Node because function doesnt know they exist
        //make a copy of degree and headptr for this and rhs
            Polynomial::Node* temp_rhs = rhs.head_ptr;
            Polynomial::Node* temp = lhs.head_ptr;
            int lhs_degree = lhs.degree;
            int rhs_degree = rhs.degree;
            
            //reducing this with data as 0
            while (temp != nullptr && temp->data == 0) {
                temp = temp->next;
                lhs_degree--;
            }
            //reducing rhs with data as 0
            while (temp_rhs != nullptr && temp_rhs->data == 0) {
                temp_rhs = temp_rhs->next;
                rhs_degree--;
            }
            
            
            while (temp != nullptr && temp_rhs != nullptr) {
                if (temp->data != temp_rhs->data) {
                    return false;
                }
                temp = temp->next;
                temp_rhs = temp_rhs->next;
                lhs_degree--;
                rhs_degree--;
            }
            //if the degrees are still not equal return false, 
            //else return true
            return (lhs_degree ==rhs_degree);
        }

    //+= operator
    Polynomial& Polynomial::operator += (const Polynomial& rhs) {
        // if the degree is less than rhs
        while (degree < rhs.degree) {
        // make nodes with a value of 0 to match the degree of rhs
        // also could have reduced rhs
        //by making a copy and doing rhs = rhs->next and rhs degree --
            Node* iter = head_ptr;
            head_ptr = new Node(0);
            head_ptr->next = iter;
            degree++;
        }
        //make a copy of degree and headptr for this and rhs
        Node* lhs_iter = head_ptr;
        Node* rhs_iter = rhs.head_ptr;
        int lhs_degree = degree;
        int rhs_degree = rhs.degree;
    
        // in the other case
        //reduce the degree and the values of lhs
        while (lhs_degree > rhs_degree) {
            lhs_iter = lhs_iter->next;
            lhs_degree--;
        }
    
      
        // here they will be the same size
        //change the data of this
        while (lhs_iter != nullptr && rhs_iter != nullptr) {
            lhs_iter->data += rhs_iter->data;
            lhs_iter = lhs_iter->next;
            rhs_iter = rhs_iter->next;
        }

        return *this;
        }

    //using horners method
    int Polynomial::evaluate(int val) const{
        int result = head_ptr->data;
        Node* temp_ptr = head_ptr;
        for (int i=1; i<=degree; i++){
            temp_ptr = temp_ptr->next;
            result = result*val + temp_ptr->data;
        }
        return result;
        }
    
    //Node cunstructor
    Polynomial::Node::Node(int data, Node* next) : 
            data(data), next(next) {}
       
    //!= operator
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
        return !(lhs == rhs);
    }

    // + operator(calls += operator on a result object)
    //result is just lhs
    //implmented as a function
    Polynomial operator + (const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial result(lhs);
        result += rhs;
        return result;
}

    }