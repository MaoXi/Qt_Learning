#include "dialog.h"
#include "ui_dialog.h"
#include"ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<mainwindow.h>

QString filename;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    filename=QFileDialog::getOpenFileName(this,"open","/","files(*)");
    ui->lineEdit->setText(filename);
}

void Dialog::on_pushButton_2_clicked()
{
    MainWindow *ptr = (MainWindow*)parentWidget();
    ptr->openf();
    this->close();
}
