#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include "course.h"



class Student
{
public:
    Student();
    Student(int id, QString fname, QString lname);

    int id;
    QString fname;
    QString lname;
    QList<Course> courses;
};

#endif // STUDENT_H
