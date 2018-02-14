#include "newcreate.h"
#include "ui_newcreate.h"
#include <QtSql>
#include <QMessageBox>
#include "login.h"

QString newCreate::tableName="";
newCreate::newCreate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newCreate)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->tableConfirmBtn->setDefault(true);
    ui->pushButton_2->setDefault(true);
    connect(ui->tableNameEditLine,SIGNAL(returnPressed()),this,SLOT(on_tableConfirmBtn_clicked()));

}
QString newCreate::realTableName="";
newCreate::~newCreate()
{
    delete ui;
}

void newCreate::on_tableConfirmBtn_clicked()
{
   QSqlDatabase db=QSqlDatabase::database("connect1");
   QSqlQuery query(db);
   realTableName=Login::username + ui->tableNameEditLine->text();
   newCreate::tableName=realTableName;
   int ok=query.exec(QString("create table %1(wkNumber varchar primary key,wkName varchar,department varchar,money double)").arg(realTableName));
   qDebug()<<ok;//如果消息处理成功就唯一，如果失败就
   if(ok==1)//QmessBox返回的是一个标准的枚举类型，16进制
   {int confirm=QMessageBox::information(0,"生成",QString("您的表格%1不存在，需要生成吗？").arg( ui->tableNameEditLine->text()),QMessageBox::Ok,QMessageBox::Cancel);
     if(confirm==QMessageBox::Ok)
     {
       QMessageBox::information(0,"生成成功",QString("您的表格%1已经生成").arg(ui->tableNameEditLine->text()),QMessageBox::Ok);
     }
     else
     {
        int shanchu=query.exec(QString("drop table %1").arg(realTableName));
        if(shanchu==1){QMessageBox::information(0,"提示",QString("您的表格%1取消生成").arg(ui->tableNameEditLine->text()),QMessageBox::Ok);}
     }
   }
   else
   {
    QMessageBox::information(0,"选择成功",QString("您的表格%1已经选择").arg(ui->tableNameEditLine->text()),QMessageBox::Ok);
    this->close();
   }


}
