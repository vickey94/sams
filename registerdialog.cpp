#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);

    this->setMaximumSize(300,380);
    this->setMinimumSize(300,380);
    this->setWindowTitle("REGISTER");
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(registerBtnSlot()));
    connect(ui->backbtn,SIGNAL(clicked()),this,SLOT(backBtnSlot()));
    connect(ui->resetbtn,SIGNAL(clicked()),this,SLOT(resetBtnSlot()));
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::backBtnSlot()
{

    this->accept();
}

void RegisterDialog::resetBtnSlot()
{

   this->clearAll();
}

void RegisterDialog::registerBtnSlot()
{

    if(ui->line_id->text()==""||ui->line_name->text()==""||ui->line_password->text()=="")
    {
        QMessageBox::warning(this,"Warning","Please input !",QMessageBox::Ok);
        return ;
    }

    if((!ui->radioButton_man->isChecked()) && (!ui->radioButton_female->isChecked()))
    {
        QMessageBox::warning(this,"Warning","Please select sex !",QMessageBox::Ok);
        return ;
    }

    if(!ui->radioButton_stu->isChecked() && !ui->radioButton_tea->isChecked())
    {
        QMessageBox::warning(this,"Warning","Please select role !",QMessageBox::Ok);
        return ;
    }

    if(!Util::NotInDB("SELECT * FROM db_school.t_student , db_school.t_teacher WHERE sid = "+ui->line_id->text()+" or tid = "+ui->line_id->text() ))
    {
        QMessageBox::warning(this,"Warning","Role already exists !",QMessageBox::Ok);
        return ;
    }

    user = new User;
    user->setId(ui->line_id->text());
    user->setPassword(ui->line_password->text());
    user->setName(ui->line_name->text());
    if(ui->radioButton_man->isChecked())
         user->setSex("man");
    else
         user->setSex("female");

    user->setCollege(ui->comboBox->currentText());

    user->setEmail(ui->line_email->text());
    user->setTel(ui->line_tel->text());

    QString str_sql ;
    if(ui->radioButton_stu->isChecked())
    {
       str_sql = "INSERT INTO db_school.t_student(sid,password,name,sex,college,email,tel) "
                            " VALUES ('"+user->getId()+"','"+user->getPassword()+"','"+user->getName()+"','"+user->getSex()+"','"+user->getCollege()+"','"+user->getEmail()+"','"+user->getTel()+"')";
    }
    else
    {
        str_sql = "INSERT INTO db_school.t_teacher(tid,password,name,sex,college,email,tel) "
                             " VALUES ('"+user->getId()+"','"+user->getPassword()+"','"+user->getName()+"','"+user->getSex()+"','"+user->getCollege()+"','"+user->getEmail()+"','"+user->getTel()+"')";
    }
    if(Util::insertOrUpdateDB(str_sql))
    {
        QMessageBox::information(this,"Tips","Success !",QMessageBox::Ok);
        this->accept();
    }
    else
        QMessageBox::information(this,"Tips","Failed",QMessageBox::Ok);
     this->clearAll();
}

void RegisterDialog::clearAll()
{
    ui->line_id->setText("");
    ui->line_name->setText("");
    ui->line_password->setText("");
    ui->line_email->setText("");
    ui->line_tel->setText("");
    ui->comboBox->setCurrentIndex(0);

}
