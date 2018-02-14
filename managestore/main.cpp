#include "mainwindow.h"
#include <QApplication>
#include "connect.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    MainWindow win;
    login.show();
    login.setFixedSize(login.width(),login.height());//先创建登陆界面，如果登录界面accept那么展示主界面
    win.setFixedSize(win.width(),win.height());
    createConnection();
    createLoginConnection();
    if(login.exec()==QDialog::Accepted)
    {
    win.show();
    return a.exec();
    }
    else
    {
    return 0;
    }

}
