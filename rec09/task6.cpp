#include <iostream>
using namespace std;

class PrintedMaterial {
    friend ostream & operator << (ostream & os, const PrintedMaterial& rhs){
          os << "numberOfPages: " << rhs.numberOfPages<<endl;
          return os;}

public:
    PrintedMaterial(unsigned count) : numberOfPages(count) {}
    void displayNumPages() const { cout << numberOfPages; }
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    //using PrintedMaterial::PrintedMaterial;
    
private:
};

class Book : public PrintedMaterial {
public:
    
    
private:
};

class TextBook : public Book {
public:
    //TextBook(unsigned count) : PrintedMaterial(count) {}
   

private:
};
class Novel : public Book {
public:
   
private:
};

// tester/modeler code
int main() {
    //TextBook text;
    ///Novel novel;
    //Magazine mag;
    PrintedMaterial pages(5);
    cout<<pages<<endl;
}