#include "changetext.h"
#include "ui_changetext.h"
#include <QtSql>
#include <QMessageBox>
#include "connect.h"
#include "newcreate.h"

changeText::changeText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::changeText)
{
    ui->setupUi(this);
    this->setWindowTitle("增加信息窗口");


}

changeText::~changeText()
{
    delete ui;
}

void changeText::on_comfirmBtn_clicked()
{
    QString wkNumber=ui->workerNumberEditLine->text();
    QString wkName=ui->workerName->text();

    QString department=ui->sectionEditLine->text();
    QString money=ui->moneyEditLine->text();
    QSqlDatabase db=QSqlDatabase::database("connect1");
    QSqlQuery query(db);

    //int ok=query.exec(QString("select wkNumber from %1 where wkNumber='%2'").arg(newCreate::realTableName,wkNumber));
    //qDebug()<<ok;
    query.exec(QString("delete from %1 where wkNumber='%2'").arg(newCreate::realTableName,wkNumber));//先删除后增加解决了无法覆盖问题，但是缺少提示

    query.exec(QString("insert into %5 values('%1','%2','%3','%4')").arg(wkNumber,wkName,department,money,newCreate::realTableName));

}
