/*
  rec07_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course;

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* cr);
    void removedFromCourse(Course* c);

private:
    string name;
    vector<Course*> courses;
};

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* stu);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar() {} 
    bool addCourse(const string& course);
    bool addStudent(const string& student);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();
    friend ostream& operator<<(ostream& os, const Registrar& rhs);

private:
    size_t findStudent(const string& stu) const;
    size_t findCourse(const string& cour) const;
    vector<Course*> courses;
    vector<Student*> students;
};


Course::Course(const string& courseName) : name(courseName) {};

const string& Course::getName() const {
        return name;
}

bool Course::addStudent(Student* stu) {
    for (Student* cur_s : students) {
        if (cur_s->getName() == stu->getName()) {
            return false;
        }
    }
    students.push_back(stu);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); i++) {
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

Student::Student(const string& name) : name(name) {}

const string& Student::getName() const {
        return name;
}
bool Student::addCourse(Course* cr) {
    for (Course* cur_cr : courses) {
        if (cur_cr->getName() == cr->getName()) {
            return false;
        }
    }
    courses.push_back(cr);
    return true;
}

void Student::removedFromCourse(Course* c) {
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i] == c) {
            courses[i] = nullptr;
            for (size_t j = i; j < courses.size() - 1; j++) {
                courses[j] = courses[j + 1];
            }
            courses.pop_back();
            break;
        }
    }
}

bool Registrar::addCourse(const string& course) {
    if (findCourse(course) == courses.size()) {
        courses.push_back(new Course(course));
        return true;
    }
    return false;
}

bool Registrar::addStudent(const string& student) {
    if (findStudent(student) == students.size()) {
        students.push_back(new Student(student));
        return true;
    }
    return false;
}

bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
    size_t i = findCourse(courseName);
    size_t j = findStudent(studentName);
    if (i == courses.size() || j == students.size()) {
        return false;
    }
    courses[i]->addStudent(students[j]);
    students[j]->addCourse(courses[i]);
    return true;
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t x = findCourse(courseName);
    if (x == courses.size()) {
        return false;
    }

    courses[x]->removeStudentsFromCourse();
    delete courses[x];

    for (size_t i = x; i < courses.size() - 1; i++) {
            courses[i] = courses[i + 1];
         }
    courses.pop_back();

    return true;

}


size_t Registrar::findStudent(const string& stu) const{
    for (size_t i = 0; i < students.size(); i++){
        if (students[i]->getName() == stu){
            return i;
        }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& cour) const{
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i]->getName() == cour){
            return i;
        }
    }
    return courses.size();
}
void Registrar::purge(){
    for (Student* stu : students){
        delete stu;
    }
    students.clear();

    for (Course* c : courses){
        delete c;
    }
    courses.clear();
}



ostream& operator<<(ostream& os, const Registrar& rhs){
    os<< "Registrar's Report" <<endl;
    os<< "Courses: " <<endl;
    if (rhs.courses.size() == 0){
        os <<endl;
    }
    else{
        for (Course* c : rhs.courses){
            os << (*c)<< endl;
        }
    }
    if (rhs.courses.size() == 0){
        os <<endl;
    }
    else{
        for (Student* s : rhs.students){
            os << (*s)<< endl;
        }
    }

    return os;
 }

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name<<' ';
    if (rhs.students.size() == 0){
        os << "No Students";
    }
    else{
        for (Student* s : rhs.students){
            os<<s->getName()<< " ";
        }
    }

    return os;

    }


ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name<<' ';
    if (rhs.courses.size() == 0){
        os << "No Students";
    }
    else{
        for (Course* c : rhs.courses){
            os<<c->getName()<< " ";
        }
    }

    return os;


}

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  
