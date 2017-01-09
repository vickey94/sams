#include "LoginDialog.h"
#include <QApplication>
#include <QIcon>
#include <QSqlDatabase>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    a.setWindowIcon(QIcon(":/res/img/logo.png"));

    //Connect mysql db_school
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("yun.vickey.me");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("db_school");

    if(db.open())
    {
        LoginDialog w;
        w.show();
        return a.exec();
    }
    else
         QMessageBox::information(NULL,"Tips","Load database failed !",QMessageBox::Yes);

    return 0;

}
