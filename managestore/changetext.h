#ifndef CHANGETEXT_H
#define CHANGETEXT_H

#include <QMainWindow>

namespace Ui {
class changeText;
}

class changeText : public QMainWindow
{
    Q_OBJECT

public:
    explicit changeText(QWidget *parent = 0);
    ~changeText();

private slots:
    void on_comfirmBtn_clicked();

private:
    Ui::changeText *ui;
};

#endif // CHANGETEXT_H
