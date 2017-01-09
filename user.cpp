#include "user.h"

User::User()
{

}

User::~User()
{

}

User::User(QString s_id,QString s_name,QString s_sex,QString s_college,QString s_email,QString s_tel)
{
    this->id = s_id;
    this->name = s_name;
    this->sex = s_sex;
    this->college = s_college;
    this->email = s_email;
    this->tel = s_tel;
}

QString User::getId()
{
    return id;
}

void User::setId(QString str)
{
    this->id = str;
}

QString User::getPassword()
{
    return password;
}

void User::setPassword(QString str)
{
    this->password = str;
}

QString User::getName()
{
    return name;
}

void User::setName(QString str)
{
    this->name = str;
}

QString User::getSex()
{
    return sex;
}

void User::setSex(QString str)
{
    this->sex = str;
}

QString User::getCollege()
{
    return college;
}

void User::setCollege(QString str)
{
    this->college = str;
}

QString User::getEmail()
{
    return email;
}

void User::setEmail(QString str)
{
    this->email = str;
}

QString User::getTel()
{
    return tel;
}

void User::setTel(QString str)
{
    this->tel = str;
}

QString User::getVip()
{
    return vip;
}

void User::setVip(QString str)
{
    this->vip = str;
}
