#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "course.h"
#include "student.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateCourses(QList<Course> courses);
    void updateStudents(QList<Student> students);
    void showBox(QString text);
private slots:
    void on_courses_clicked(const QModelIndex &index);

    void on_addCourse_clicked();

    void on_addUser_clicked();

    void on_students_clicked(const QModelIndex &index);

    void on_addC2S_clicked();

    void on_addMark_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
