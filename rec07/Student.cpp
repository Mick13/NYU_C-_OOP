#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {


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

}