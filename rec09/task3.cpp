#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned count) : numberOfPages(count) {}
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    //using PrintedMaterial::PrintedMaterial;
    Magazine(unsigned count) : PrintedMaterial(count) {}
private:
};

class Book : public PrintedMaterial {
public:
    
    Book(unsigned count) : PrintedMaterial(count) {}
private:
};

class TextBook : public Book {
public:
    //TextBook(unsigned count) : PrintedMaterial(count) {}
    TextBook(unsigned count) : Book(count) {}

private:
};
class Novel : public Book {
public:
    Novel(unsigned count) : Book(count) {}
private:
};

// tester/modeler code
int main() {
    TextBook text;
    Novel novel;
    Magazine mag;
}