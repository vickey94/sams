#ifndef TEACHER_H
#define TEACHER_H

#include "user.h"

class Teacher : public User
{
public:
    Teacher();
    Teacher(QString s_id,QString s_name,QString s_sex,QString s_college,QString s_email,QString s_tel);
    ~Teacher();

    QString getCourse();
    void setCourse(QString str);

private:
    QString course;
};

#endif // TEACHER_H
