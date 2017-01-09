#include "teacherdialog.h"
#include "ui_teacherdialog.h"

TeacherDialog::TeacherDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherDialog)
{
    ui->setupUi(this);





    ui->tabWidget->setCurrentIndex(0);

    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(TabSlots(int)));
    connect(ui->pushButton_edit,SIGNAL(clicked()),this,SLOT(editBtnSlot()));
    connect(ui->pushButton_save,SIGNAL(clicked()),this,SLOT(saveBtnSlot()));
    connect(ui->pushButton_logout,SIGNAL(clicked()),this,SLOT(logoutBtnSlot()));
    connect(ui->pushButton_search,SIGNAL(clicked()),this,SLOT(searchBtnSlot()));
    connect(ui->pushButton_search_2,SIGNAL(clicked()),this,SLOT(searchBtnSlot_2()));

    connect(ui->stuview, SIGNAL(clicked(QModelIndex)),this,SLOT(stuviewClickedSlot(QModelIndex)));
    connect(ui->pushButton_submit_2,SIGNAL(clicked()),this,SLOT(submitORupdateStuScoreSlot()));
    connect(ui->pushButton_delete,SIGNAL(clicked()),this,SLOT(deleteBtnSlot()));
    connect(ui->pushButton_open,SIGNAL(clicked()),this,SLOT(openBtnSlot()));

    connect(ui->pushButton_update,SIGNAL(clicked()),this,SLOT(updateBtnSlot()));
    connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(modelChangeSlot(QModelIndex,QModelIndex)));


    connect(ui->stuInfoView,SIGNAL(clicked(QModelIndex )),this,SLOT(stuInfoViewClickedSlot(QModelIndex)));
    connect(ui->pushButton_refrsesh,SIGNAL(clicked()),this,SLOT(refreshBtnSlot()));
    connect(ui->pushButton_search_4,SIGNAL(clicked()),this,SLOT(searchBtnSlot_4()));
    connect(ui->pushButton_insert,SIGNAL(clicked()),this,SLOT(insertBtnSlot()));
    connect(ui->pushButton_delete_2,SIGNAL(clicked()),this,SLOT(deleteBtnSlot_2()));




}

TeacherDialog::~TeacherDialog()
{
    delete ui;
}

void TeacherDialog::getTeacherFromLogin(Teacher * teacher)
{

    this->tea = teacher;
    ui->label_sid->setText(tea->getId());
    ui->label_name->setText(tea->getName());
    ui->label_course->setText(tea->getCourse());

}

//page_1
void TeacherDialog::getTeaInfo()
{
    model->setTable("t_teacher");
    model->setFilter("tid = "+tea->getId());
    model->select();
    QSqlRecord record=model->record(0);

    tea = new Teacher(record.value("tid").toString(),record.value("name").toString(),
                           record.value("sex").toString(),record.value("college").toString(),
                           record.value("email").toString(),record.value("tel").toString());
    tea->setCourse(record.value("course").toString());

    ui->line_id->setText(tea->getId());
    ui->line_name->setText(tea->getName());
    ui->line_email->setText(tea->getEmail());
    ui->line_tel->setText(tea->getTel());

    ui->comboBox->setCurrentText(tea->getCollege());
    if (tea->getSex()== "man")
    {
        ui->radioButton_man->click();
    }
    else
    {
        ui->radioButton_female->click();
    }

    ui->comboBox_2->setCurrentText(tea->getCourse());

    ui->frame->setEnabled(false);

    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_save->setEnabled(false);

}
//page_2
void TeacherDialog::getTeaResult(QString str_sql)
{

      qmodel = new QSqlQueryModel();

      qmodel->setQuery(str_sql);
      qmodel->setHeaderData(0, Qt::Horizontal, tr("Years"));
      qmodel->setHeaderData(1, Qt::Horizontal, tr("Courses"));
      qmodel->setHeaderData(2, Qt::Horizontal, tr("Sid"));
      qmodel->setHeaderData(3, Qt::Horizontal, tr("Name"));
      qmodel->setHeaderData(4, Qt::Horizontal, tr("Colleges"));
      qmodel->setHeaderData(5, Qt::Horizontal, tr("Scores"));

      //set sort
      QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
      sqlproxy->setSourceModel(qmodel);

      ui->scoreview->setModel(sqlproxy);

      ui->scoreview->resizeColumnsToContents();

}

//page_2
void TeacherDialog::getVIPResultData(QString str_sql)
{


    vipmodel = new QSqlQueryModel();

    vipmodel->setQuery(str_sql);
    vipmodel->setHeaderData(0, Qt::Horizontal, tr("Years"));
    vipmodel->setHeaderData(1, Qt::Horizontal, tr("Courses"));
    vipmodel->setHeaderData(2, Qt::Horizontal, tr("AVG"));
    vipmodel->setHeaderData(3, Qt::Horizontal, tr("MAX"));
    vipmodel->setHeaderData(4, Qt::Horizontal, tr("MIN"));
    vipmodel->setHeaderData(5, Qt::Horizontal, tr("EXCELLENT"));
    vipmodel->setHeaderData(6, Qt::Horizontal, tr("PASS"));
    vipmodel->setHeaderData(7, Qt::Horizontal, tr("PASS FAIL"));

    //set sort
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(vipmodel);

    ui->scoreview_vip->setModel(sqlproxy);
    ui->scoreview_vip->resizeColumnsToContents();
}

// page_3
void TeacherDialog::getStudentView(QString str_sql)
{
    qmodel = new QSqlQueryModel();
    qmodel->setQuery(str_sql);
    qmodel->setHeaderData(0, Qt::Horizontal, tr("Years"));
    qmodel->setHeaderData(1, Qt::Horizontal, tr("Sid"));
    qmodel->setHeaderData(2, Qt::Horizontal, tr("Name"));
    qmodel->setHeaderData(3, Qt::Horizontal, tr("Courses"));
    qmodel->setHeaderData(4, Qt::Horizontal, tr("Scores"));

  //  qDebug()<<qmodel->rowCount();
    //set sort
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(qmodel);

    ui->stuview->setModel(sqlproxy);
    ui->stuview->resizeColumnsToContents();
}

void TeacherDialog::TabSlots(int index)
{


    switch(index)
    {

    case 0:

    case 1: this->getTeaInfo(); break;

    case 2: this->searchBtnSlot(); break;

    case 3: this->searchBtnSlot_2();break;

    case 4: this->searchBtnSlot_4();break;
    }

}

void TeacherDialog::editBtnSlot()
{
     ui->frame->setEnabled(true);
     ui->pushButton_edit->setEnabled(false);
     ui->pushButton_save->setEnabled(true);
}

void TeacherDialog::saveBtnSlot()
{

    ui->frame->setEnabled(false);
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_save->setEnabled(false);

    tea->setName(ui->line_name->text());
    if(ui->radioButton_man->isChecked())
        tea->setSex("man");
    else
        tea->setSex("female");

    tea->setCollege(ui->comboBox->currentText());
    tea->setEmail(ui->line_email->text());
    tea->setTel(ui->line_tel->text());
    tea->setCourse(ui->comboBox_2->currentText());

    model->setTable("t_teacher");
    model->setFilter("tid = "+tea->getId());
    model->select();

    QSqlRecord record=model->record(0);

    model->setData(model->index(0,2),tea->getName());
    model->setData(model->index(0,3),tea->getSex());
    model->setData(model->index(0,4),tea->getCollege());
    model->setData(model->index(0,5),tea->getEmail());
    model->setData(model->index(0,6),tea->getTel());
    model->setData(model->index(0,7),tea->getCourse());
    if(model->submitAll())

        QMessageBox::information(this,"Tips","SUCCESS !",QMessageBox::Ok);

    else

        QMessageBox::information(this,"Tips","FAILED !",QMessageBox::Ok);


}
void TeacherDialog::searchBtnSlot()
{

    QString str_year =  ui->comboBox_year->currentText();
    QString str_course = ui->comboBox_course->currentText();
    QString str_sid = ui->lineEdit_sid->text();


    QString str1 = "SELECT tr.year, tr.course, tr.sid ,ts.name , ts.college , tr.score   FROM t_result AS tr , t_student  AS ts  WHERE tr.sid = ts.sid ";
    QString str_vip1 = "SELECT t.year,t.course,AVG(score),MAX(score),MIN(score) ,SUM(t.score>75),SUM(t.score>60), SUM(t.score<60) FROM t_result AS t ";
    QString str_vip2 = " GROUP BY t.course,t.year ORDER BY  t.year desc ";
    QString temp = "WHERE";
    if(str_year != "")
    {
        str1 = str1 + " AND tr.year = '"+ str_year +"' " ;
        temp = temp + " t.year = '" + str_year+"' ";
    }

    if(str_course != "")
    {
        str1 = str1 + " AND tr.course = '"+ str_course+"' ";

        if(temp != "WHERE")
          temp = temp + " AND ";

         temp = temp + " t.course = '" + str_course+"' ";

    }

    if(str_sid != "")
    {
        str1 = str1 + " AND tr.sid = '"+ str_sid+"' ";

        if(temp != "WHERE")
            temp = temp + " AND ";

        temp = temp + " t.sid = '"+str_sid+"' ";
    }

    if(temp != "WHERE")

        str_vip1 = str_vip1 +temp+ str_vip2;

    else
        str_vip1 = str_vip1 + str_vip2;

    qDebug()<< str1;
    qDebug()<<str_vip1 ;
    this->getTeaResult(str1);
    this->getVIPResultData(str_vip1);

}

void TeacherDialog::searchBtnSlot_2()
{
    QString str_year =  ui->comboBox_year_3->currentText();
    QString str_course = ui->comboBox_course_3->currentText();
    QString str_sid = ui->lineEdit_sid_3->text();


    QString str1 = "SELECT tr.year ,ts.sid , ts.name, tr.course,tr.score "
                   "FROM db_school.t_result AS tr, db_school.t_student AS ts "
                   "WHERE tr.sid = ts.sid";


    if(str_year != "")
    {
        str1 = str1 + " AND tr.year = '"+ str_year +"' " ;

    }

    if(str_course != "")
    {
        str1 = str1 + " AND tr.course = '"+ str_course+"' ";

    }

    if(str_sid != "")
    {
        str1 = str1 + " AND tr.sid = '"+ str_sid+"' ";

    }


    qDebug()<< str1;

    this->getStudentView(str1);

}

void TeacherDialog::searchBtnSlot_4()
{
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_delete_2->setEnabled(false);

    model->setTable("t_student");

    model->removeColumn(1); //remove password
    model->removeColumn(6); //remove vip



    if(ui->comboBox_college->currentIndex()!=0)
        model->setFilter("college = '"+ui->comboBox_college->currentText()+"'");
    if(ui->lineEdit_sid_6->text()!="")
        model->setFilter("sid = "+ui->lineEdit_sid_6->text());

    model->select();

    model->setHeaderData(0,Qt::Horizontal,"Sid");
    model->setHeaderData(1,Qt::Horizontal,"Name");
    model->setHeaderData(2,Qt::Horizontal,"Sex");
    model->setHeaderData(3,Qt::Horizontal,"College");
    model->setHeaderData(4,Qt::Horizontal,"E-mail");
    model->setHeaderData(5,Qt::Horizontal,"Tel");

    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(model);

    ui->stuInfoView->setModel(sqlproxy);
    ui->stuInfoView->resizeColumnsToContents();

}

void TeacherDialog::logoutBtnSlot()
{
    if(QMessageBox::question(this,"Tips","LOG OUT ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
      {
      emit toLoginDialog();
      delete this;
      }
}

void TeacherDialog::stuviewClickedSlot(QModelIndex index)
{
    if(index.isValid())
    {
        QSqlRecord record = qmodel->record(index.row());

        ui->comboBox_year_2->setCurrentText(record.value("year").toString());
        ui->comboBox_course_2->setCurrentText(record.value("course").toString());
        ui->lineEdit_sid_2->setText(record.value("sid").toString());
        ui->lineEdit_name_2->setText(record.value("name").toString());
        ui->lineEdit_score_2->setText(record.value("score").toString());

    }

}

void TeacherDialog::stuInfoViewClickedSlot(QModelIndex index)
{
    if(index.isValid())
    {
        ui->pushButton_delete_2->setEnabled(true);
    }
}

void TeacherDialog::submitORupdateStuScoreSlot()
{
    QString sid = ui->lineEdit_sid_2->text();
    QString year = ui->comboBox_year_2->currentText();
    QString course = ui->comboBox_course_2->currentText();
    QString name = ui->lineEdit_name_2->text();
    QString score = ui->lineEdit_score_2->text();

    if(Util::NotInDB("SELECT * FROM db_school.t_student WHERE sid = '"+ sid+"'"))
    {
       if(QMessageBox::question(this,"Tips","This student not in the database ,  Do you want to insert now ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
       {
          ui->tabWidget->setCurrentIndex(4);
          ui->line_id_2->setText(ui->lineEdit_sid_2->text());
       }
       return;
    }

    if(sid==""||year==""||course==""||score=="")
    {
       QMessageBox::warning(this,"Warning","Please input !");
       return;
    }

    QString str_sql = "SELECT * FROM db_school.t_result WHERE sid = '"+ sid+
            "' AND year = '" +year+ "' AND course = '"+ course+"'";

    qDebug()<<str_sql;
    //qDebug()<<Util::NotInDB(str_sql);

    QString str_iu = "";

    if(Util::NotInDB(str_sql))

        str_iu = "INSERT INTO db_school.t_result(sid,year,course,score) VALUES ('"+sid+"','"+year+"','"+course+"','"+score+"')";

    else

        str_iu = "UPDATE db_school.t_result SET score = '"+ score +"' WHERE sid = '"+ sid +"' AND year = '"+ year +"' AND course = '" + course+"'";


    qDebug()<<str_iu;
    if(Util::insertOrUpdateDB(str_iu))
    {
        QMessageBox::information(this,"Tips","SUCCESS !",QMessageBox::Ok);
        this->searchBtnSlot_2(); //refresh tableview
        ui->pushButton_update->setEnabled(false);
    }
    else
        QMessageBox::warning(this,"Warning","Failed !");

    ui->lineEdit_sid_2->setText("");
    ui->lineEdit_name_2->setText("");
    ui->lineEdit_score_2->setText("");

}

void TeacherDialog::modelChangeSlot(QModelIndex m1, QModelIndex m2)
{
 //   qDebug()<<m1;
    ui->pushButton_update->setEnabled(true);

}

void TeacherDialog::updateBtnSlot()
{
    if(model->submitAll())
        QMessageBox::information(this,"Tips","Update student information success !",QMessageBox::Ok);
    else
        QMessageBox::warning(this,"Warning","Update failed !");
}

void TeacherDialog::refreshBtnSlot()
{

    ui->comboBox_college->setCurrentIndex(0);
    ui->lineEdit_sid_6->setText("");
    model->revertAll();

    this->searchBtnSlot_4();
}

void TeacherDialog::insertBtnSlot()
{
    if(((ui->line_id_2->text() == "")||(ui->line_password->text() == ""))||(ui->line_name_2->text()==""))
    {
        QMessageBox::warning(this,"Warning","Please insert student data !");
        return ;
    }

    Student *stu = new Student();
    stu->setId(ui->line_id_2->text());
    stu->setPassword(ui->line_password->text());
    stu->setName(ui->line_name_2->text());

    if(ui->radioButton_man_2->isChecked())
        stu->setSex("man");
    else
        stu->setSex("female");

    stu->setCollege(ui->comboBox_college_2->currentText());
    stu->setEmail(ui->line_email_2->text());
    stu->setTel(ui->line_tel_2->text());
    stu->setVip("0");

    QString str_sql = "SELECT * FROM db_school.t_student WHERE sid = "+ stu->getId() ;
//qDebug()<<str_sql;
    if(Util::NotInDB(str_sql))
    {
        str_sql = "INSERT INTO db_school.t_student(sid,password,name,sex,college,email,tel,vip) "
                  " VALUES ('"+stu->getId()+"','"+stu->getPassword()+"','"+stu->getName()+"','"+stu->getSex()+"','"+stu->getCollege()+"','"+stu->getEmail()+"','"+stu->getTel()+"','"+stu->getVip()+"')";
//qDebug()<<str_sql;
        if(Util::insertOrUpdateDB(str_sql))
            QMessageBox::information(this,"Tips","Insert student information success !",QMessageBox::Ok);
        else
            QMessageBox::warning(this,"Warning","Insert failed !");
    }
    else
        QMessageBox::information(this,"Tips","Student data already exists ! Please update on the left table ",QMessageBox::Ok);

    this->clearAllInsert();
    this->searchBtnSlot_4();
}

void TeacherDialog::clearAllInsert()
{
    ui->line_id_2->setText("");
    ui->line_password->setText("");
    ui->line_name_2->setText("");
    ui->line_email_2->setText("");
    ui->line_tel_2->setText("");

}

void TeacherDialog::getDataFromFile(QString file_name)
{
    //read data
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QMessageBox::warning(this,"Warning","Cannot open file !");
         return ;
    }

    QStringList list;
    list.clear();
    QTextStream in(&file);  //QTextStream read data

    QSqlQuery query;
    int i = 0;
    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        list = fileLine.split(",");

        query.prepare("INSERT INTO db_school.t_result (sid,year,course,score) VALUES (:sid,:year,:course,:score)");
        query.bindValue(":sid",list.at(0));
        query.bindValue(":year",list.at(1));
        query.bindValue(":course",list.at(2));
        query.bindValue(":score",list.at(3));
        query.exec();
        i++;
    }
    query.clear();
    QMessageBox::information(this,"Tips",QString::number(i)+" data has been inserted",QMessageBox::Ok);

}

void TeacherDialog::openBtnSlot()
{
    QString file_name = QFileDialog::getOpenFileName (this, "Open file", "","*.csv" );

    if(file_name == "")
        return ;

    qDebug()<<file_name;
    this->getDataFromFile(file_name);
    ui->label_filename->setText(file_name);
    this->searchBtnSlot_2();
}

void TeacherDialog::deleteBtnSlot()
{
    QString sid = ui->lineEdit_sid_2->text();
    QString year = ui->comboBox_year_2->currentText();
    QString course = ui->comboBox_course_2->currentText();

    if(sid==""||year==""||course=="")
    {
       QMessageBox::warning(this,"Warning","Please input !");
       return;
    }

    if(Util::NotInDB("SELECT * FROM db_school.t_student WHERE sid = '"+ sid+"'"))
    {
       QMessageBox::warning(this,"Warning","This student not in the database ,  Please insert first !");

       return;
    }
    //check result
    if(Util::NotInDB("SELECT * FROM db_school.t_result WHERE sid = '"+ sid+"' AND year = '" +year+ "' AND course = '"+course+"'"))
    {
     QMessageBox::information(this,"Tips","Database does not have this data !",QMessageBox::Ok);
     return ;
    }

    QString str_sql = "DELETE FROM db_school.t_result WHERE sid = '"+ sid+
            "' AND year = '" +year+ "' AND course = '"+ course+"'";
    QSqlQuery query;

    query.exec(str_sql);
    QMessageBox::information(this,"Tips","Data has been deleted",QMessageBox::Ok);

    ui->comboBox_course_2->setCurrentIndex(0);
    ui->comboBox_year_2->setCurrentIndex(0);
    ui->lineEdit_sid_2->setText("");
    ui->lineEdit_name_2->setText("");
    ui->lineEdit_score_2->setText("");
    this->searchBtnSlot_2();

}

void TeacherDialog::deleteBtnSlot_2()
{

    if(QMessageBox::question(this,"Tips","Confirm delete data ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        model->removeRow(ui->stuInfoView->currentIndex().row());
        model->submitAll();
        this->searchBtnSlot_4();
    }

}

