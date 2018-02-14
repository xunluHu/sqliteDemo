#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect.h"
#include "changetext.h"
#include <QMessageBox>
#include "newcreate.h"
#include <QProcess>
#include <QPrinter>
#include <QPrintDialog>
#include <QPaintDevice>
#include  "qpainter.h"//这。。。
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPixmap>
#include <QDateTime>
#include <QFileDialog>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("欢迎使用员工奖金管理系统");
    ui->tableView->setSortingEnabled(true);
    this->setFixedSize(this->width(),this->height());
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(actionOpenNotepate()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->actionPrint,SIGNAL(triggered(bool)),this,SLOT(doprintf()));
    connect(ui->actionScreenCapture,SIGNAL(triggered(bool)),this,SLOT(ScreenCapture()));
    connect(ui->actionBrowser,SIGNAL(triggered(bool)),this,SLOT(browserView()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showBtn_clicked()
{
    //QSqlDatabase db=QSqlDatabase::database("connect1");
    //QSqlQuery query(db);
    //query.exec(QString("select * from %1").arg(newCreate::realTableName));

 model=new QSqlTableModel(this,QSqlDatabase::database("connect1"));//多个数据库要指定自己的数据库


 model->setTable(QString("%1").arg(newCreate::realTableName));

 model->setHeaderData(0,Qt::Horizontal,QObject::tr("工号"));//如果没有手动设置会自己创建的
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("部门"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("欠款"));

 model->select();
 model->setEditStrategy(QSqlTableModel::OnManualSubmit);
 ui->tableView->setModel(model);
 //ui->tableView->setCornerButtonEnabled(false);
 //总数计算

 QSqlDatabase db=QSqlDatabase::database("connect1");
 QSqlQuery query(db);
 query.exec(QString("select money from %1").arg(newCreate::realTableName));
 double count=0;
 while(query.next())
 {
     count+=query.value(0).toDouble();
 }
 QString count1=QString::number(count);

 ui->sumLineEdit->setText(count1);

 //最高欠款计算
 QSqlQuery query2(db);
 query2.exec(QString("select * from %1").arg(newCreate::realTableName));
 double highestCount=0;
 QString wkName;
 while(query2.next())
 {
     if(highestCount<query2.value(3).toDouble())
     {
         highestCount=query2.value(3).toDouble();
         wkName=query2.value(1).toString();
     }
 }
 QString stringMuchMoney=QString::number(highestCount);

 ui->maxlineEdit->setText(QString("%1(%2)").arg(stringMuchMoney,wkName));



}
void MainWindow::on_addBtn_clicked()
{

    changeText*table=new changeText;
    table->show();

}

void MainWindow::on_deleteBtn_clicked()
{
    QSqlQuery query;
    query.exec(QString("drop table %1").arg(newCreate::realTableName));
}

void MainWindow::on_newCreateTableBtn_clicked()
{
    newCreate*table=new newCreate;
    table->show();

}
void MainWindow::on_confirmBtn_clicked()
{

    if(model!=NULL)
   {
        model->database().transaction();
    if(model->submitAll()){
        model->database().commit();
       QMessageBox::warning(this,"信息" ,"保存成功",QMessageBox::Ok);
    }else{
        //model->database().rollback();
        //QMessageBox::warning(this,"错误" ,"回滚失败",QMessageBox::Ok);
    }
    }


}
void MainWindow::actionOpenNotepate()
{
    QProcess *pro=new QProcess(this);
    pro->start("notepad");
}
void MainWindow::doprintf()
{

       QPrinter printer(QPrinter::HighResolution);

       QPrintPreviewDialog preview(&printer,0);


       connect(&preview, SIGNAL(paintRequested(QPrinter *)),this,SLOT(plotPic(QPrinter *)));

       preview.exec();

}
void MainWindow::plotPic(QPrinter *printer)
{


    QPainter painter(printer);
    QPixmap image;

    image=image.grabWidget(this,10,100,422,380); /* 绘制窗口至画布 */
    QRect rect = painter.viewport();
    QSize size = image.size();
    size.scale(rect.size(), Qt::KeepAspectRatio);     //此处保证图片显示完整
    painter.setViewport(rect.x(), rect.y(),size.width(), size.height());
    painter.setWindow(image.rect());
    painter.drawPixmap(0,0,image); /* 数据显示至预览界面 */

}
 void MainWindow::ScreenCapture()
 {
     dlg=new QDialog(this);
     dlg->setWindowTitle("截屏");
     spinBox=new QSpinBox(dlg);
     QPushButton*pushButton=new QPushButton(dlg);
     pushButton->setText("确定");
     QHBoxLayout * lay=new QHBoxLayout(dlg);
     QLabel *label=new QLabel("几秒后执行: ");
     lay->addWidget(label);
     lay->addWidget(spinBox);
     lay->addWidget(pushButton);
     connect(pushButton,SIGNAL(clicked(bool)),SLOT(ScreenCapturetime()));


     dlg->exec();


 }
 void MainWindow::ScreenCapturetime()
 {
     dlg->hide();
     timer=new QTimer(this);
     timer->start(spinBox->value()*1000);
     connect(timer,SIGNAL(timeout()),this,SLOT(realScreenCapture()));
 }
 void MainWindow::realScreenCapture()
 {

     pixmap=QPixmap::grabWindow(this->winId());
     qDebug()<<this->winId();
     dlg->show();
     timer->stop();
     QDateTime dataTime=QDateTime::currentDateTime();
     QString time=dataTime.toString("yyyy-MM-dd hh:mm:ss");
     QString fileName=QFileDialog::getSaveFileName(this,"Save file",QDir::currentPath(),"(*.png)");
     pixmap.save(fileName);

 }


void MainWindow::on_checkBtn_clicked()
{
    QSqlDatabase db=QSqlDatabase::database("connect1");
    QSqlQuery query(db);
    QSqlTableModel * selectedModel=new QSqlTableModel(this,QSqlDatabase::database("connect1"));
    QString str=newCreate::realTableName;//表名
    QString currentText=ui->comboBox->currentText();
    QString tableValue=ui->lineEdit->text();
    selectedModel->setHeaderData(0,Qt::Horizontal,QObject::tr("工号"));//如果没有手动设置会自己创建的
    selectedModel->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
    selectedModel->setHeaderData(2,Qt::Horizontal,QObject::tr("部门"));
    selectedModel->setHeaderData(3,Qt::Horizontal,QObject::tr("欠款"));
    if(currentText=="工号")
    {
      selectedModel->setTable(str);
      selectedModel->setFilter(QString("wkNumber='%1'").arg(tableValue));
      selectedModel->select();
      ui->tableView->setModel(selectedModel);
    }
    else if(currentText=="姓名")
    {
        selectedModel->setTable(str);
        selectedModel->setFilter(QString("wkName='%1'").arg(tableValue));
        selectedModel->select();
        ui->tableView->setModel(selectedModel);
    }
    else if(currentText=="部门")
    {
        selectedModel->setTable(str);
        selectedModel->setFilter(QString("department='%1'").arg(tableValue));
        selectedModel->select();
        ui->tableView->setModel(selectedModel);
    }
    else if(currentText=="欠款")
    {
        selectedModel->setTable(str);
        selectedModel->setFilter(QString("money='%1'").arg(tableValue.toDouble()));
        selectedModel->select();
        ui->tableView->setModel(selectedModel);
    }

}

void MainWindow::browserView()
{
    web=new myWeb;
    web->setWindowTitle("浏览器");
    web->webView=new QWebView(web);
    QVBoxLayout *lay2=new QVBoxLayout(web);
    QLabel  *label=new QLabel(web);
    label->setText("请输入地址：");
    lineEdit=new QLineEdit(web);
    QPushButton *frontBtn=new QPushButton(web);
    QPushButton *backBtn=new QPushButton(web);
    QHBoxLayout *lay=new QHBoxLayout;
    lay2->addLayout(lay);
    lay->addWidget(label);
    lay->addWidget(lineEdit);
    lay->addWidget(frontBtn);
    lay->addWidget(backBtn);
    //lay2->addStretch(1);
    lay2->addWidget(web->webView);

    frontBtn->setText("前进");
    backBtn->setText("后退");

    lineEdit->setText("http://www.baidu.com");
    QString str=lineEdit->text();

    url.setUrl(str);
    web->webView->load(url);
    web->webView->setWindowTitle("百度");
    QWebSettings *settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);

    web->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);//浏览器的代理模式
    connect(web->webView,SIGNAL(linkClicked(QUrl)),this,SLOT(webClick(QUrl)));
    web->show();
    connect(this->lineEdit,SIGNAL(returnPressed()),this,SLOT(webReload()));
    connect(backBtn,SIGNAL(clicked(bool)),web->webView,SLOT(back()));
    connect(frontBtn,SIGNAL(clicked(bool)),web->webView,SLOT(forward()));
    connect(web->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(titleChange(QUrl)));


}

void MainWindow::webClick(QUrl url)
{
    web->webView->load(url);
}
void MainWindow::webReload()
{
    QString str=this->lineEdit->text();
    QUrl newUrl;
    newUrl.setUrl(str);
    web->webView->load(newUrl);

}
void MainWindow::titleChange(QUrl url)
{
    this->lineEdit->setText(url.toString());
}
















