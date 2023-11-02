#include <iostream>
#include <string>
#include <vector>

#ifndef Registrar_H
#define Registrar_H

namespace BrooklynPoly {
    class Student;
    class Course;

    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        bool addCourse(const std::string& course);
        bool addStudent(const std::string& student);
        bool enrollStudentInCourse(const std::string& studentName, const std::string& courseName);
        bool cancelCourse(const std::string& courseName);
        void purge();
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);

    private:
        size_t findStudent(const std::string& stu) const;
        size_t findCourse(const std::string& cour) const;
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}

#endif