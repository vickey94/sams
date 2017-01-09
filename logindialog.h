#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H


#include "registerdialog.h"
#include "studentmanagedialog.h"
#include "student.h"
#include "teacher.h"
#include <mainwindow.h>
#include <QDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();


private:
    Ui::LoginDialog *ui;
    QSqlTableModel *model;

    StudentManageDialog *stuManage ;
    Student  * student;

  //  TeacherDialog *teaManage;
    Teacher * teacher;

    MainWindow * teaManage;



signals:
    void toStudentManage(Student *);
    void toTeacherManage(Teacher *);


private slots:
    bool inputIsEmpty(); //determine whether the input is empty
    void inputClear();
    void loginbtnSlot();
    void registerbtnSlot();
    void useridInputSlot(const QString &);


};

#endif // LOGINDIALOG_H
