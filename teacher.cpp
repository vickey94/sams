#include "teacher.h"

Teacher::Teacher()
{

}
Teacher::~Teacher()
{

}


Teacher:: Teacher(QString s_id,QString s_name,QString s_sex,QString s_college,QString s_email,QString s_tel):User(s_id,s_name,s_sex,s_college,s_email,s_tel)
{

}

QString Teacher::getCourse()
{
    return course;
}

void Teacher::setCourse(QString str)
{
    this->course = str;
}
