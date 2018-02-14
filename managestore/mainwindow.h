#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QDialog>
#include <QSpinBox>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QDir>
#include <QtWebKit>
#include <QWebView>
#include <QUrl>
#include "myweb.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPrinter myprinter;
    QDialog *dlg;
    QSpinBox * spinBox;
    QTimer * timer;
    QPixmap pixmap;
    QUrl url;
    QLineEdit *lineEdit;
    myWeb* web;
signals:

private slots:


    void on_showBtn_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void on_newCreateTableBtn_clicked();

    void on_confirmBtn_clicked();

    void actionOpenNotepate();

    void doprintf();

    void plotPic(QPrinter *printer);

    void ScreenCapture();

    void ScreenCapturetime();

    void realScreenCapture();

    void browserView();

    void on_checkBtn_clicked();

    void webClick(QUrl);

    void webReload();
    void titleChange(QUrl);



private:
    Ui::MainWindow *ui;
QSqlTableModel*model=NULL;
};

#endif // MAINWINDOW_H
