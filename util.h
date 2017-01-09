#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QAxObject>
#include <QSqlQueryModel>
#include <QFile>
#include <QDir>
#include <QDebug>

class Util
{
public:
    Util();

    static bool NotInDB(const QString &str_sql); //To determine if there is already exists in MySQL

    static bool insertOrUpdateDB(const QString &str_sql);

    static bool exportExcel(QString filePath,QSqlQueryModel *);

private:

};

#endif // UTIL_H
