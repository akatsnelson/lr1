#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "singleton.h"

#include <QMessageBox>
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCourses(QList<Course> courses)
{
    ui->courses->clear();
    for (auto c  : courses){
        auto id = QString::number(c.id);
        ui->courses->addItem("Id:"+id + " " + c.name);
    }
}

void MainWindow::updateStudents(QList<Student> students)
{
    ui->students->clear();
    for (auto s  : students){
        auto id = QString::number(s.id);
        ui->students->addItem("Id:"+id + " " + s.fname + " " + s.lname);
    }
}


void MainWindow::on_courses_clicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    int id = index.row();
    auto courses = Singleton::getInstance()->courses;

    auto c = courses[id];
    msgBox.setText("Курс: "+ c.name + "\n" + "Формула оценки: дз*0."+ QString::number(c.hw) + "+ с/р*0." + QString::number(c.sr)
                   + "+ сем*0." + QString::number(c.sem)+ "+ п/р*0." + QString::number(c.pr)+ "+ экз*0." + QString::number(c.exam));
    msgBox.exec();

}


void MainWindow::on_students_clicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    int id = index.row();
    auto students = Singleton::getInstance()->students;

    auto s = students[id];
    QString courses_str = "";
    for (auto c : s.courses){
        int itog = c.sem_m*c.sem/100 + c.exam_m*c.exam/100 + c.sr_m*c.sr/100 + c.pr_m*c.pr/100 + c.hw_m*c.hw/100;
        courses_str += "\nКурс: "+ c.name  +  "\nдз - "+ QString::number(c.hw_m) + "+ с/р - " + QString::number(c.sr_m)
        + "+ сем - " + QString::number(c.sem_m)+ "+ п/р - " + QString::number(c.pr_m)+ "+ экз - " + QString::number(c.exam_m) +"\n" +
        "Итог - " + QString::number(itog);
    }
    msgBox.setText("Фамилия: "+ s.lname + "\n" +
                "Имя: "+ s.lname + "\n" +
                "Курсы: " + "\n" + courses_str);
    msgBox.exec();
}


void MainWindow::showBox(QString text){
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::on_addCourse_clicked()
{
    auto courses = Singleton::getInstance()->courses;
    int id = Singleton::getInstance()->courses_id;
    QString name = ui->name->text();
    int exam = ui->exam->text().toInt();
    int hw = ui->hw->text().toInt();
    int sr = ui->sr->text().toInt();
    int sem = ui->sem->text().toInt();
    int pr = ui->pr->text().toInt();
    if (exam + hw+ sr+sem+pr == 100){
        auto c = Course(id, name, exam, hw, sr, sem, pr);
        courses.append(c);
        Singleton::getInstance()->courses = courses;
        Singleton::getInstance()->courses_id++;
        updateCourses(courses);
        showBox("Курс успешно добавлен!");
    } else{
        showBox("Неверная формула!");
    }

}


void MainWindow::on_addUser_clicked()
{
    auto students = Singleton::getInstance()->students;
    int id = Singleton::getInstance()->students_id;
    QString fname = ui->fname->text();
    QString lname = ui->lname->text();
    auto s = Student(id, fname, lname);
    students.append(s);
    Singleton::getInstance()->students = students;
    Singleton::getInstance()->students_id++;
    updateStudents(students);
    showBox("Студент успешно добавлен!");

}



void MainWindow::on_addC2S_clicked()
{
    auto students = Singleton::getInstance()->students;
    auto courses = Singleton::getInstance()->courses;
    auto s_id = ui->sa_id->text().toInt();
    auto c_id = ui->ca_id->text().toInt();
    int student_id = -1;
    int course_id = -1;
    Course course;

    for (auto i = 0; i < students.size(); i++){
        if (students[i].id == s_id){
            student_id = i;
        }
    }

    for (auto i = 0; i < courses.size(); i++){
        if (courses[i].id == c_id){
            course_id = i;
            course = courses[course_id];
        }
    }

    if (student_id == -1){
        showBox("Нет такого студента");
        return;
    }

    if (course_id == -1){
        showBox("Нет такого курса");
        return;
    }

    for (auto c: students[student_id].courses){
        if (c.id == c_id){
            showBox("Курс уже добавлен");
            return;
        }
    }
    course.sr_m = 0;
    course.exam_m = 0;
    course.hw_m = 0;
    course.pr_m = 0;
    course.sem_m = 0;

    students[student_id].courses.append(course);
    Singleton::getInstance()->students = students;

    showBox("Курс добавлен!");
}


void MainWindow::on_addMark_clicked()
{

    auto students = Singleton::getInstance()->students;
    auto courses = Singleton::getInstance()->courses;
    auto s_id = ui->sm_id->text().toInt();
    auto c_id = ui->cm_id->text().toInt();


    int hw_m = ui->hw_m->text().toInt();
    int sr_m = ui->sr_m->text().toInt();
    int pr_m = ui->pr_m->text().toInt();
    int sem_m = ui->sem_m->text().toInt();
    int exam_m = ui->exam_m->text().toInt();

    int student_id = -1;
    int course_id = -1;
    Course course;

    for (auto i = 0; i < students.size(); i++){
        if (students[i].id == s_id){
            student_id = i;
        }
    }

    for (auto i = 0; i < courses.size(); i++){
        if (courses[i].id == c_id){
            course_id = i;
            course = courses[course_id];
        }
    }

    if (student_id == -1){
        showBox("Нет такого студента");
        return;
    }

    if (course_id == -1){
        showBox("Нет такого курса");
        return;
    }

    for (auto i = 0; i < students[student_id].courses.size(); i++){
        if (students[student_id].courses[i].id == c_id){
            course.exam_m = exam_m;
            course.sr_m = sr_m;
            course.pr_m = pr_m;
            course.hw_m = hw_m;
            course.sem_m = sem_m;
            students[student_id].courses[i] = course;
            Singleton::getInstance()->students = students;
            showBox("Оценки обновлены");
            return;
        }
    }

    showBox("У студента нет такого курса.");

}

