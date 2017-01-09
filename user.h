#ifndef USER_H
#define USER_H

#include <QStringList>

class User
{
public:
    User();
    User(QString s_id,QString s_name,QString s_sex,QString s_college,QString s_email,QString s_tel);
    ~User();


    QString getId();
    void setId(QString str);

    QString getPassword();
    void setPassword(QString str);

    QString getName();
    void setName(QString str);

    QString getSex();
    void setSex(QString str);

    QString getCollege();
    void setCollege(QString str);

    QString getEmail();
    void setEmail(QString str);

    QString getTel();
    void setTel(QString str);

    QString getVip();
    void setVip(QString str);

protected:
    QString id ;
    QString password;
    QString name;
    QString sex;
    QString college;
    QString email;
    QString tel;
    QString vip;

};

#endif // USER_H
