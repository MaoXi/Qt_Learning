#include "dialog.h"
#include "ui_dialog.h"
#include"add.h"

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

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::on_pushButton_clicked()
{
    bool ok;
    QString str1=ui->lineEdit->text();
    QString str2=ui->lineEdit_2->text();

    int int1=str1.toInt(&ok);
    int int2=str2.toInt(&ok);

    int a;
    a=m(int1,int2);
    ui->lineEdit_3->setText(QString::number(a));
    //在lineedit输出int型变量
}

void Dialog::on_pushButton_2_clicked()
{
    int b;
    b=suiji();
    ui->lineEdit_4->setText(QString::number(b));
}
