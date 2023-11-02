#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
	: numOfPages(numPages)
    {}
    void displayNumPages() const { cout << numOfPages; }
private:
    unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
	: PrintedMaterial(numPages)
    {}
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
	: PrintedMaterial(numPages)
    {}
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs )
	: Book(numPages),
	  numOfIndexPages(numIndxPgs)
    {}
    void displayNumPages() const {
    // cant acces number of pages... need a getter
    cout<<"***"<<endl;
	cout << "Pages: ";
	PrintedMaterial::displayNumPages();
	cout << "\n Index pages: ";
	cout << numOfIndexPages << endl; 
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
	: Book(numPages)
    {}
private:
};

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);
    PrintedMaterial pt(5);

    text.displayNumPages();
    cout << "===========\n";
    novel.displayNumPages();
    cout << "===========\n";
    mag.displayNumPages();
    cout << "===========\n";
}