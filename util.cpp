#include "util.h"
#include <QSqlQuery>

Util::Util()
{

}

bool Util::NotInDB(const QString &str_sql)
{

    QSqlQuery query;

    query.exec(str_sql);
    if(query.next())
        return false;
    else
        return true;

}

bool Util::insertOrUpdateDB(const QString &str_sql)
{

    QSqlQuery query ;
    query.prepare(str_sql);
    return query.exec();


}

bool Util::exportExcel(QString filePath, QSqlQueryModel *model)
{
    QAxObject *work_book = NULL;
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    excel.setProperty("DisplayAlerts", false);//no warning
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    QFile xlsFile(filePath);
    if (xlsFile.exists())
    {
        work_book = work_books->querySubObject("Open(const QString &)", filePath);
    }
    else {
        work_books->dynamicCall("Add");
        work_book = excel.querySubObject("ActiveWorkBook");
    }
    QAxObject *work_sheets = work_book->querySubObject("Sheets");
    QAxObject *first_sheet = work_sheets->querySubObject("Item(int)", 1);

    QAxObject *cell ;


   for(int i=0;i<model->rowCount();i++)
   {
       cell = first_sheet->querySubObject("Cells(int,int)", 1, i+1);
       cell->setProperty("Value",  model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());

   }

   for(int i=0;i<model->rowCount();i++)
    {
        for(int j=0;j<model->columnCount();j++)
        {
           cell = first_sheet->querySubObject("Cells(int,int)", i+2, j+1);
           cell->setProperty("Value", model->data(model->index(i,j)).toString());
        }
    }

    work_book->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath)); //
    work_book->dynamicCall("Close(Boolean)", false);  //close file
    excel.dynamicCall("Quit(void)");  //exit

    return true;
}


