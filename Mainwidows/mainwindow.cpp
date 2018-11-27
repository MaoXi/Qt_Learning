#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ui_dialog.h"
#include"dialog.h"
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QTextBrowser>

extern QString filename;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));  //tabCloseRequested为自带信号，使用之前setTabsClosable(true)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::removeSubTab(int index)        //关闭标签页的槽
{
      ui->tabWidget->removeTab(index);
}

void MainWindow::openf()
{
    QTextBrowser *t=new QTextBrowser();
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text))
        qDebug() << "Can not open";
    QTextStream s(&file);
    t->setText(s.readAll());
    ui->tabWidget->addTab(t,filename);
    ui->tabWidget->setTabsClosable(true);
}

void MainWindow::on_actionnew_triggered()
{
   //n.show();                              //exec和show的区别：exec弹出窗口关闭前后主窗口为非活动
   n.exec();
}

void MainWindow::on_actionopen_triggered()
{
    Dialog subwin(this);                   //"this" is very important.   子窗口
 // subwin.setGeometry(x()-100, y()+100, wifth()-100, height()-100);
    subwin.exec();
}
