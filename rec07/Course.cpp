#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly{

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
}
