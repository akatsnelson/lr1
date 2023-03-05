#ifndef COURSE_H
#define COURSE_H

#include <QMap>
#include <Qstring>



class Course
{
public:
    Course();
    Course(int id, QString name, int exam, int hw, int sr, int sem, int pr);

    int id;
    QString name;
    int exam;
    int hw;
    int sr;
    int sem;
    int pr;

    int exam_m;
    int hw_m;
    int sr_m;
    int sem_m;
    int pr_m;

};

#endif // COURSE_H
