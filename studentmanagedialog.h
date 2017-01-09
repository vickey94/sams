#ifndef STUDENTMANAGEDIALOG_H
#define STUDENTMANAGEDIALOG_H

#include "student.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDialog>
#include <QSortFilterProxyModel>



namespace Ui {
class StudentManageDialog;
}

class StudentManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentManageDialog(QWidget *parent = 0);
    ~StudentManageDialog();
    Student * stu ;
private slots:
     void getStudentFromLogin(Student *);
     void TabSlots(int index);
     void editBtnSlot();
     void saveBtnSlot();
     void logoutBtnSlot();

signals:
     void toLoginDialog();


private:
     void getStuInfo();
     void getStuScore();

     void getVIPScoreData(QString year,QString course);

     Ui::StudentManageDialog *ui;
     QSqlTableModel *model;

     QSqlQueryModel *qmodel;


};

#endif // STUDENTMANAGEDIALOG_H
