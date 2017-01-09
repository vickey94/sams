#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //create QSqlTableModel
    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);  //

    //set tips
    this->setWindowTitle("Logining");

    //set icon
   this->setWindowIcon(QIcon(":/res/img/logo.png"));

    ui->logolabel->setPixmap(QPixmap(":/res/img/loging.png").scaled(ui->logolabel->size()));
   ui->label_head->setPixmap(QPixmap(":/res/img/head/default.png").scaled(ui->label_head->size()));
    //
    this->setMaximumSize(540,360);
    this->setMinimumSize(540,360);

    //connect signal and slot
    connect(ui->loginbtn,SIGNAL(clicked()),this,SLOT(loginbtnSlot()));
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerbtnSlot()));

    connect(ui->useridline, SIGNAL(textChanged(const QString &)), this,SLOT(useridInputSlot(const QString &)));

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::inputIsEmpty()
{

    if(ui->useridline->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","sid/tid can't empty !");
        return false;
    }

    if(ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","Password can't empty !");
        return false;
    }

    if(!ui->radioButton_stu->isChecked()&&!ui->radioButton_tea->isChecked())
    {
        QMessageBox::warning(this,"Warning","Please select a role !");
        return false;
    }
    return true;

}

void LoginDialog::loginbtnSlot()
{

    if(!inputIsEmpty())
    {
       ui->passwordline->clear();
       return;
    }

    // role is student
    if(ui->radioButton_stu->isChecked())
    {
        model->setTable("t_student");

        QString str = "sid = " + ui->useridline->text() ;
        model->setFilter(str);
        model->select();

        if(model->rowCount()>0)
        {
            QSqlRecord record=model->record(0);
            if(record.value("password")==ui->passwordline->text())
            {

               student = new Student(record.value("sid").toString(),record.value("name").toString(),
                                     record.value("sex").toString(),record.value("college").toString(),
                                     record.value("email").toString(),record.value("tel").toString());


             //   QMessageBox::information(this,"Tips","Login Success ! Welcome To Student Achievement Management System",QMessageBox::Ok);

                this->inputClear();

                //create student manage dialog
                stuManage = new StudentManageDialog();

                //connect  signal and slot
                connect(stuManage,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                stuManage->show();

                connect(this,SIGNAL(toStudentManage(Student*)),stuManage,SLOT(getStudentFromLogin(Student*)));
                emit toStudentManage(student);

                this->hide();

                return;
            }
            else
            {
               QMessageBox::information(this,"Tips","Password error !",QMessageBox::Ok);
               return;
            }
        }
        else
        {
           QMessageBox::warning(this,"Tips","Role does not exist please register",QMessageBox::Yes);

           this->inputClear();
           return;
        }

    }

    //role is teacher
    if(ui->radioButton_tea->isChecked())
    {
        model->setTable("t_teacher");

        QString str = "tid = " + ui->useridline->text() ;
        model->setFilter(str);
        model->select();

        if(model->rowCount()>0)
        {
            QSqlRecord record=model->record(0);
            if(record.value("password")==ui->passwordline->text())
            {

               teacher = new Teacher(record.value("tid").toString(),record.value("name").toString(),
                                     record.value("sex").toString(),record.value("college").toString(),
                                     record.value("email").toString(),record.value("tel").toString());
               teacher->setCourse(record.value("course").toString());

              //  QMessageBox::information(this,"Tips","Login Success ! Welcome To Student Achievement Management System",QMessageBox::Ok);

                this->inputClear();

                //create teacher manage dialog

               // teaManage = new TeacherDialog();
                 teaManage = new MainWindow();
                //connect  signal and slot
                connect(teaManage,SIGNAL(toLoginDialog()),this,SLOT(showNormal()));
                teaManage->show();

                connect(this,SIGNAL(toTeacherManage(Teacher*)),teaManage,SLOT(getTeacherFromLogin(Teacher *)));
                emit toTeacherManage(teacher);

                this->hide();

                return;
            }
            else
            {
               QMessageBox::information(this,"Tips","Password error !",QMessageBox::Ok);
               return;
            }
        }
        else
        {
           QMessageBox::warning(this,"Tips","Role does not exist please register",QMessageBox::Yes);

           this->inputClear();
           return;
        }

    }



}

void LoginDialog::registerbtnSlot()
{

    RegisterDialog d(this);

    this->hide();

    if(d.exec()==QDialog::Accepted)
    {
        this->showNormal();
    }
    this->inputClear();
}

void LoginDialog::inputClear()
{
    ui->useridline->clear();
    ui->passwordline->clear();
}

void LoginDialog::useridInputSlot(const QString &)
{

    QFileInfo fi(":/res/img/head/"+ui->useridline->text()+".png");
   if( fi.isFile())
   ui->label_head->setPixmap(QPixmap(":/res/img/head/"+ui->useridline->text()+".png").scaled(ui->label_head->size()));

}

