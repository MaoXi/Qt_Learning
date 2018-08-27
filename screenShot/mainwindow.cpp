#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_pushButton_clicked()
{
    QPixmap pix;
    pix=ui->centralWidget->grab(QRect(20,50,500,300));                                                    //设置截图区域
    QString fpath=QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss")  + ".bmp";                 //文件路径 以时间命名
    pix.save(QCoreApplication::applicationDirPath()+"//"+fpath,"bmp");                                    //保存
    QMessageBox::information(this,"tip","ok",QMessageBox::Ok);                                            //弹出提示框
}
