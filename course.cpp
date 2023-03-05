#include "course.h"

Course::Course()
{

}


Course::Course(int idd, QString n, int e, int h, int s, int se, int p)
{
    id = idd;
    name = n;
    exam = e;
    hw = h;
    sr = s;
    sem = se;
    pr = p;
}
