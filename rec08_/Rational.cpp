#include "Rational.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

namespace CS2124{
    

ostream& operator<<(ostream& os, const Rational& rhs){
    if (rhs.num == 0){
            os << 0<<endl;
        }
        else{
            os << rhs.num <<"/" <<rhs.den<<endl;
        }
        return os;
    }


Rational::Rational(int numerator, int denominator) : num(numerator), den(denominator) {
        normalize();
    }
Rational::operator bool() const {
	    return num != 0;
	    
}
Rational& Rational::operator= (const Rational& rhs){
        if (&rhs != this){
            num = rhs.num;
            den = rhs.den;
        }
        return *this;
    }
    
Rational& Rational::operator+=(const Rational& rhs) {
	num = (num * rhs.den + rhs.num * den);
	den = den * rhs.den;
	normalize();
	return *this;
    }
    

Rational Rational::operator++(int){
        Rational result(*this);
        num += den;
        normalize();
	    return result;
    }
    
Rational& Rational::operator++(){
        num += den;
        normalize();
	    return *this;
    } 
    
void Rational::normalize() {
        if (den == 0){
            cerr <<"DENOMINATOR CANT BE 0"<<endl;
            return;
        }
        if (num ==0) {
            return;
        }
        else if  (den < 0 && num < 0){
            den *= -1;
            num *=-1;
        }
        else if  (den < 0 && num > 0){
            den *=-1;
            num *=-1; 
        }
        int factor  = greatestCommonDivisor(abs(num), abs(den));
        num /= factor;
        den /= factor;

        }
        
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;}
    

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.den == rhs.den && lhs.num == rhs.num);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    if (lhs.num < 0 and rhs.num > 0 ){
        return true;
    }
    if (lhs.num > 0 and rhs.num < 0 ){
        return false;
    }   
    bool neg;
    if (lhs.num < 0 and rhs.num < 0 ){
        neg = true;
    }
    if (neg){
        return !(lhs.num * rhs.den < lhs.den * rhs.num);
    }
    return (lhs.num * rhs.den < lhs.den * rhs.num);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs == rhs || lhs<rhs);
}

bool operator > (const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs || lhs<rhs);
}

bool operator >=(const Rational& lhs, const Rational& rhs) {
    return !(lhs<rhs);
}

istream& operator>>(istream& ifs, Rational& rhs){
        char slash;
        ifs>>rhs.num>>slash>>rhs.den;
        //rhs = Rational(a,b);
        rhs.normalize();
        return ifs;
}

Rational operator--(Rational& lhs, int) {
    Rational result(lhs);
    lhs += -1;
    return result;
}
Rational& operator--(Rational& rhs){
    rhs += -1;
    return rhs;
    
}


int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

}