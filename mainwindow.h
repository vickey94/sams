#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "teacher.h"
#include "student.h"
#include "util.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QStatusBar>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

namespace Ui {
class MainWindow;
}
//Teacher Manage Dialog
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Teacher * tea;

private slots:
     void settimeline();
     void getTeacherFromLogin(Teacher *teacher);
     void TabSlots(int index);
     void editBtnSlot();
     void saveBtnSlot();
     void searchBtnSlot();   //get all students scores
     void searchBtnSlot_2(); //insert or update student scores
     void searchBtnSlot_4(); //insert or update student information
     void logoutBtnSlot();

     void deleteBtnSlot();
     void submitORupdateStuScoreSlot();

     void openBtnSlot();

     void stuviewClickedSlot(QModelIndex);
     void stuInfoViewClickedSlot(QModelIndex);
     void modelChangeSlot(QModelIndex, QModelIndex);

     void updateBtnSlot();  //update student information
     void refreshBtnSlot();
     void deleteBtnSlot_2();
     void insertBtnSlot(); //insert new student

     void exportExcelBtnSlot();


signals:
     void toLoginDialog();

private:

     void getTeaInfo();
     void getTeaResult(QString str_sql);

     void getVIPResultData(QString str_sql);

     void getStudentView(QString str_sql);

     void clearAllInsert();

     void getDataFromFile(QString file_name); //read from csv

     Ui::MainWindow *ui;
     QSqlTableModel *model;   //for teacher table
     QSqlQueryModel *qmodel;  //for teacher get result by option
     QSqlQueryModel *vipmodel;//for teacher get statistical information
     QTimer *timelinetimer;

     QLabel * statusLabel ;
     QLabel * timestatusLabel ;
};

#endif // MAINWINDOW_H
