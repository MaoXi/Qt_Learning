#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include"QGridLayout"
#include"ui_juzhen.h"
#include"test.h"

int sample_Num;                        //样本数目
int sample_M;                         //抽样方法
double h[20][20];                      //不确定度、协方差矩阵
double g[20];                          //均值
int k[5];                              //sigma
double global;                         //参数量
double s_Result[500][20];

QString name[20][20];

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


void Widget::on_spinBox_editingFinished()                 //参数量填写框
{
    int a;
    a=ui->spinBox->value();
    int global1=ui->spinBox->value();
    global=global1;

    ui->comboBox->clear();
    for(int i=1;i<=a;i++)
    {
        ui->comboBox->addItem(QString::number(i));        //输入参数页下拉框1
        ui->comboBox_5->addItem(QString::number(i));     //数理统计页下拉框
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
        ui->comboBox_3->addItem(b+"-"+QString::number(i+b2));   //参数输入页下拉框2
    }
}

void Widget::on_pushButton_5_clicked()
{
    QString ava=ui->lineEdit_2->text();
    QString num3=ui->lineEdit_3->text();

    double ava_int=ava.toDouble();
    double num3_int=num3.toDouble();

    int b=ui->comboBox->currentIndex();
    int c=ui->comboBox_8->currentIndex();
         k[b]=c+1;                                     //sigma
         h[b][b]=num3_int;                             //不确定度
         g[b]=ava_int;
         name[b][b]=ui->lineEdit->text();
         qDebug()<<h[b][b]<<g[b]<<endl;
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        juzhen.showme();
        //juzhen.addname();
}

void Widget::on_pushButton_6_clicked()                    //协方差
{
    QString num4=ui->lineEdit_4->text();
    double num4_int=num4.toDouble();
    int j=ui->comboBox_3->currentIndex();
    int i=ui->comboBox->currentIndex();
      h[i][j+i+1]=num4_int;
      h[j+i+1][i]=num4_int;
      name[i][j+i+1]=ui->lineEdit->text();
      name[j+i+1][i]=ui->lineEdit->text();
      qDebug()<<i<<h[i][j+1]<<endl;
      ui->lineEdit_4->clear();
      juzhen.showme();
      //juzhen.addname();
}


void Widget::on_spinBox_2_editingFinished()         //样本数
{
    sample_Num=ui->spinBox_2->value();
}

void Widget::on_comboBox_4_currentIndexChanged(const QString &arg1)  //抽样方法，数字0-3对应不同抽样方法
{
    sample_M=ui->comboBox_4->currentIndex();
}

void Widget::on_pushButton_8_clicked()                          //开始抽样计算
{
          f(h,g,sample_Num,global,sample_M,k,s_Result);         //模拟

          for(int ii=0;ii<sample_Num;ii++)
          {
              for(int jj=0;jj<global;jj++)
              {
                qDebug()<<ii<<" "<<jj<<"  "<<s_Result[ii][jj];
              }
           }
}



void Widget::on_comboBox_5_currentIndexChanged(int index)
{
    ui->lineEdit_6->setText(QString::number(g[index]));
    ui->lineEdit_9->setText(QString::number(h[index][index]));
}
