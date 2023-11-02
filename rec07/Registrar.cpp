#include "Course.h"
#include "Student.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly{

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

};