#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"


class Student:public User
{
public:
    Student();
    Student(QString s_id,QString s_name,QString s_sex,QString s_college,QString s_email,QString s_tel);
    ~Student();

};

#endif // STUDENT_H
