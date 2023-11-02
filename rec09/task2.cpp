#include <iostream>
using namespace std;

class PrintedMaterial {
public:
private:
    unsigned numberOfPages
};

class Magazine : public PrintedMaterial {
public:
private:
    unsigned numberOfPages
};

class Book : public PrintedMaterial {
public:
private:
    unsigned numberOfPages
};

class TextBook : public Book {
public:
private:
    unsigned numberOfPages
};

class Novel : public Book {
public:
private:
    unsigned numberOfPages
};

// tester/modeler code
int main() {
    TextBook text;
    Novel novel;
    Magazine mag;
}