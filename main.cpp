#include "Singleton.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    auto courses = Singleton::getInstance()->courses;
    auto students = Singleton::getInstance()->students;
    QApplication a(argc, argv);
    MainWindow w;
    w.updateCourses(courses);
    w.updateStudents(students);
    w.show();
    return a.exec();
}
