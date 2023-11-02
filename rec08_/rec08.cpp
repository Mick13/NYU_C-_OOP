#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int greatestCommonDivisor(int x, int y);

class Rational{

    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend istream& operator>>(istream& ifs, Rational& rhs);
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



int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
        
}

ostream& operator<<(ostream& os, const Rational& rhs){
        if (rhs.num == 0){
            os << 0<<endl;
        }
        else{
            os << rhs.num <<"/" <<rhs.den<<endl;
        }
        return os;
    }

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
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
