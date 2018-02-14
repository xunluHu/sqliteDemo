#ifndef NEWCREATE_H
#define NEWCREATE_H

#include <QWidget>

namespace Ui {
class newCreate;
}

class newCreate : public QWidget
{
    Q_OBJECT

public:
    explicit newCreate(QWidget *parent = 0);
    ~newCreate();
    static QString tableName;
    static QString realTableName;
private slots:
    void on_tableConfirmBtn_clicked();

private:
    Ui::newCreate *ui;
};

#endif // NEWCREATE_H
