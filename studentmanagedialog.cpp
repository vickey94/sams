#include "studentmanagedialog.h"
#include "ui_studentmanagedialog.h"
#include <QDebug>

StudentManageDialog::StudentManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentManageDialog)
{
    ui->setupUi(this);


    ui->tabWidget->setCurrentIndex(0);

    this->setWindowTitle("Student Manage");
    this->setMaximumSize(525,490);
    this->setMinimumSize(525,490);

    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    //
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(TabSlots(int)));

    connect(ui->pushButton_edit,SIGNAL(clicked()),this,SLOT(editBtnSlot()));
    connect(ui->pushButton_save,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
    connect(ui->pushButton_logout,SIGNAL(clicked()),this,SLOT(logoutBtnSlot()));

}

StudentManageDialog::~StudentManageDialog()
{
    delete ui;
}

void StudentManageDialog::getStudentFromLogin(Student* student)
{

    this->stu = student;
    ui->label_sid->setText(stu->getId());
    ui->label_name->setText(stu->getName());

    ui->label_head->setPixmap(QPixmap(":/res/img/head/"+stu->getId()+".png").scaled(ui->label_head->size()));

}

void StudentManageDialog::TabSlots(int index)
{


    switch(index)
    {

    case 0:

    case 1: this->getStuInfo(); break;

    case 2: this->getStuScore(); break;
    }

}

void StudentManageDialog::getStuInfo()
{
    model->setTable("t_student");
    model->setFilter("sid = "+stu->getId());
    model->select();
    QSqlRecord record=model->record(0);

    stu = new Student(record.value("sid").toString(),record.value("name").toString(),
                           record.value("sex").toString(),record.value("college").toString(),
                           record.value("email").toString(),record.value("tel").toString());

    ui->line_id->setText(stu->getId());
    ui->line_name->setText(stu->getName());
    ui->line_email->setText(stu->getEmail());
    ui->line_tel->setText(stu->getTel());

    ui->comboBox->setCurrentText(stu->getCollege());


    if (stu->getSex()== "man")
    {
        ui->radioButton_man->click();
    }
    else
    {
        ui->radioButton_female->click();
    }


    ui->frame->setEnabled(false);

    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_save->setEnabled(false);

}

void StudentManageDialog::getStuScore()
{

    model->setTable("t_result");

    model->removeColumn(0);
    model->removeColumn(0);

    model->setHeaderData(0,Qt::Horizontal,"Years");
    model->setHeaderData(1,Qt::Horizontal,"Courses");
    model->setHeaderData(2,Qt::Horizontal,"Scores");


    //set view can not change
    ui->scoreview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoreview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QString str = "sid = "+stu->getId();

    model->setFilter(str);
    model->select();

    ui->scoreview->setModel(model);


    qmodel = new QSqlQueryModel();
    QString str1 = "SELECT t.year,t.course,AVG(score),MAX(score),MIN(score) FROM t_result AS t GROUP BY t.course,t.year ";
    qmodel->setQuery(str1);
    qmodel->setHeaderData(0, Qt::Horizontal, tr("Years"));
    qmodel->setHeaderData(1, Qt::Horizontal, tr("Courses"));
    qmodel->setHeaderData(2, Qt::Horizontal, tr("AVG"));
    qmodel->setHeaderData(3, Qt::Horizontal, tr("MAX"));
    qmodel->setHeaderData(4, Qt::Horizontal, tr("MIN")); 

    //set sort
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(qmodel);
    ui->scoreview_vip->setModel(sqlproxy);

  //  ui->scoreview_vip->setModel(qmodel);
}

void StudentManageDialog::editBtnSlot()
{
     ui->frame->setEnabled(true);
     ui->pushButton_edit->setEnabled(false);
     ui->pushButton_save->setEnabled(true);
}

void StudentManageDialog::saveBtnSlot()
{

    ui->frame->setEnabled(false);
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_save->setEnabled(false);

    stu->setName(ui->line_name->text());
    if(ui->radioButton_man->isChecked())
        stu->setSex("man");
    else
        stu->setSex("female");

    stu->setCollege(ui->comboBox->currentText());
    stu->setEmail(ui->line_email->text());
    stu->setTel(ui->line_tel->text());

    model->setTable("t_student");
    model->setFilter("sid = "+stu->getId());
    model->select();

    QSqlRecord record=model->record(0);

    model->setData(model->index(0,2),stu->getName());
    model->setData(model->index(0,3),stu->getSex());
    model->setData(model->index(0,4),stu->getCollege());
    model->setData(model->index(0,5),stu->getEmail());
     model->setData(model->index(0,6),stu->getTel());

    if(model->submitAll())

        QMessageBox::information(this,"Tips","SUCCESS !",QMessageBox::Ok);

    else

        QMessageBox::information(this,"Tips","FAILED !",QMessageBox::Ok);


}

void StudentManageDialog::getVIPScoreData(QString year,QString course)
{
  /*  QString str = "SELECT AVG(score),MAX(score),MIN(score) FROM t_result AS t WHERE t.year = "+year
            +" AND t.course= "+course;
    QSqlQuery query();
                while (query.next()) {
                    QString country = query.value(0).toString();
                    qDebug()<<country;
                }
*/
}
void StudentManageDialog::logoutBtnSlot()
{
  if(QMessageBox::question(this,"Tips","LOG OUT ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
    emit toLoginDialog();
    delete this;
    }
}
