#include <iostream>
#include <fstream>

#ifndef RATIONAL_H
#define RATIONAL_H

namespace CS2124{
    int greatestCommonDivisor(int x, int y);

    class Rational{

        friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
        friend std::istream& operator>>(std::istream& ifs, Rational& rhs);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);


    public:
        Rational(int numerator = 0, int denominator = 1);
        Rational& operator= (const Rational& rhs);
        Rational& operator+=(const Rational& rhs);
        
        explicit operator bool() const;
        
        Rational operator++(int);
        Rational& operator++();  

    private:
        int num;
        int den;    

        void normalize();

};

Rational operator--(Rational& lhs, int);
Rational& operator--(Rational& rhs);
Rational operator+(const Rational& lhs, const Rational& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator > (const Rational& lhs, const Rational& rhs);

bool operator >=(const Rational& lhs, const Rational& rhs);
    
}




#endif