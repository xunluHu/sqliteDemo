#include "login.h"
#include "ui_login.h"
#include "connect.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("登录");
    ui->userNameLineEdit->setFocus();
    ui->loginBtn->setDefault(true);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);



}
QString Login::username="";
Login::~Login()
{
    delete ui;
}
void Login::on_registerBtn_clicked()
{
    QString userName = ui->userNameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QSqlDatabase db1=QSqlDatabase::database("connect2");
    QSqlQuery query1(db1);
    if(!userName.isEmpty() && !password.isEmpty())
    {
        query1.exec(QString("create table users(userName varchar primary key,password varchar)"));
        int ok=query1.exec(QString("insert into users values('%1','%2')").arg(userName,password));
        if (ok==1)
        {
            QMessageBox::warning(0,"恭喜","保存成功",QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(0,"嘿嘿","已经注册过惹",QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::warning(0,"麻烦","请输入用户名和密码",QMessageBox::Ok);
    }

}

void Login::on_loginBtn_clicked()
{
    username=ui->userNameLineEdit->text();
    QSqlDatabase db1=QSqlDatabase::database("connect2");
    QSqlQuery query2(db1);
    query2.exec("select * from users");
    int var=0;
    while(query2.next())
    {
        if(query2.value(0).toString()==username && query2.value(1).toString()==ui->passwordLineEdit->text() )
        {
            QDialog::accept();
            var=1;
        }
    }
    if(var==0)
    {
        QMessageBox::warning(0,"提示","你的账号或者密码有误，请重新输入",QMessageBox::Cancel);

                ui->passwordLineEdit->clear();
                ui->userNameLineEdit->setFocus();
    }
}

void Login::on_quitBtn_clicked()
{
    QDialog::reject();
}
