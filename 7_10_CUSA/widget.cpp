#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include"QGridLayout"
#include"ui_juzhen.h"


double h[20][20];
double g[20];
double global;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
   // QWidget *widget1 = new QWidget;
   // ui->tabWidget->addTab(widget1,"test");
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



void Widget::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void Widget::on_spinBox_editingFinished()
{
    int a;
    a=ui->spinBox->value();
    int global1=ui->spinBox->value();
    global=global1;

    ui->comboBox->clear();
    for(int i=1;i<=a;i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }
}

void Widget::on_pushButton_7_clicked()
{
     ui->tabWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
    form.show();
 }


void Widget::on_pushButton_4_clicked()           //矩阵预览
{
    juzhen.show();
    //juzhen.showme();
}

void Widget::on_pushButton_3_clicked()            //生成矩阵
{
   // h[20][20]={0};
    juzhen.showme();
}


void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
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

void Widget::on_pushButton_5_clicked()
{
    QString ava=ui->lineEdit_2->text();
    QString num3=ui->lineEdit_3->text();

    double ava_int=ava.toDouble();
    double num3_int=num3.toDouble();

    int b=ui->comboBox->currentIndex();
         h[b][b]=num3_int;
         g[b]=ava_int;
         qDebug()<<h[b][b]<<g[b]<<endl;
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        juzhen.showme();
        //juzhen.addname();
}

void Widget::on_pushButton_6_clicked()
{
    QString num4=ui->lineEdit_4->text();
    double num4_int=num4.toDouble();
    int j=ui->comboBox_3->currentIndex();
    int i=ui->comboBox->currentIndex();
      h[i][j+i+1]=num4_int;
      h[j+i+1][i]=num4_int;
      qDebug()<<i<<h[i][j+1]<<endl;
      ui->lineEdit_4->clear();
      juzhen.showme();
      //juzhen.addname();
}


