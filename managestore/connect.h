#ifndef CONNECT_H
#define CONNECT_H
#include <QtSql>
#include<QMessageBox>

static bool createConnection()
{
    QSqlDatabase db1=QSqlDatabase::addDatabase("QSQLITE","connect1");
    db1.setDatabaseName("myData.db");
    return db1.open();
    if(!db1.open())
    {
        QMessageBox::warning(0,"不好意思","内部数据数据库没有打开",QMessageBox::Ok);
    }
}
static bool createLoginConnection()
{
    QSqlDatabase db2=QSqlDatabase::addDatabase("QSQLITE","connect2");
    db2.setDatabaseName("myLogin.db");
    return db2.open();
    if(!db2.open())
    {
        QMessageBox::warning(0,"不好意思","数据库没有打开",QMessageBox::Ok);
    }

}

#endif // CONNECT_H

