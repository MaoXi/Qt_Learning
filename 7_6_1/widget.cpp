#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QDateTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::on_spinBox_editingFinished()
{
    int a;
    a=ui->spinBox->value();

    ui->comboBox->clear();
    for(int i=1;i<=a;i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }

}

void Widget::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString ava=ui->lineEdit_2->text();
    QString num3=ui->lineEdit_3->text();
    double ava_int=ava.toDouble();
    double num3_int=num3.toDouble();
    QFile data("D:/Qt/my.txt");
    if(!data.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
       {
          QMessageBox::warning(this,"!","can't open",QMessageBox::Yes);
       }

         QTextStream out(&data);
         out<<name<<" "<<"ava:"<<ava_int<<"  num2:"<<num3_int<<endl;
         QMessageBox::warning(this,":)","sucess!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
  }
