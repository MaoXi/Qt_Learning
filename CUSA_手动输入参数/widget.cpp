#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QDateTime>
#include<qdebug.h>

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
        //ui->comboBox_3->addItem(QString::number(i));
    }
}

void Widget::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_3->clear();
    bool ok;
    QString b;
    int a;
    a=ui->spinBox->value();
    b=ui->comboBox->currentText();
    int b2=b.toInt(&ok);
    for(int i=1;i<=a-b2;i++)
    {
        ui->comboBox_3->addItem(b+"-"+QString::number(i+b2));
    }

}

void Widget::on_pushButton_clicked()
{
    QString ava=ui->lineEdit_2->text();
    QString num3=ui->lineEdit_3->text();
    QString num4=ui->lineEdit_4->text();
    double ava_int=ava.toDouble();
    double num3_int=num3.toDouble();
    double num4_int=num4.toDouble();
    bool ok;
    QString b=ui->comboBox->currentText();
    int b2=b.toInt(&ok);
    QFile data("D:/Qt/不确定度.txt");
    if(!data.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
       {
          QMessageBox::warning(this,"!","can't open",QMessageBox::Yes);
       }

         QTextStream out(&data);
         if(b2!=1)
             out<<"\n";
         out<<"para"<<b2<<": "<<num3_int<<"\n";
         QMessageBox::warning(this,":)","sucess!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
  }


void Widget::on_pushButton_2_clicked()
{
     QString num4=ui->lineEdit_4->text();
     double num4_int=num4.toDouble();
     int j=ui->comboBox_3->currentIndex();
     QFile data("D:/Qt/协方差.txt");
     if(!data.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
        {
           QMessageBox::warning(this,"!","can't open",QMessageBox::Yes);
        }
       QTextStream out2(&data);
       if(j==0)
           out2<<"\n";
       out2<<num4_int<<"   ";
       ui->lineEdit_4->clear();
}
