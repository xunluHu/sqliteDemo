#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    static QString username;

private slots:



    void on_registerBtn_clicked();

    void on_loginBtn_clicked();

    void on_quitBtn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
