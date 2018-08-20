#include "widget.h"
#include "string.h"
#include "ui_widget.h"
#include<QDebug>
#include"QGridLayout"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include"ui_juzhen.h"
//#include"test.h"
#include"interface3.h"
#include"mams.h"
#include"k_s.h"
#include"cpd.h"
#include "widget.h"
#include<QtDataVisualization/Q3DBars.h>
#include<QColor>
#include<QColormap>

using namespace QtDataVisualization;

int sample_Num;                        //样本数目
int item_num;
int sample_M;                         //抽样方法
double **h;                      //不确定度、协方差矩阵
double *g;                          //均值
int *k;                              //sigma
int global;                         //参数量
double **s_Result;
int ks_global = 0;
int combox6 = 0;

int number_gruop3 = 0,number_gruop4 = 0,number_gruop5 = 0;
double *average,*rsd,**cc,**cov,**rcov;                         //数理统计结果指针
double *prob_normal,*prob_uni,*prob_expcdf;                     //k-s检验结果
double **x_sample,**y_sample,**x_normal,**y_normal,**x_uniform,**y_uniform,**x_exponential,**y_exponential;    //累计概率密度
QString *name[1000];

QGridLayout *mainLayout0= new QGridLayout;
QGridLayout *mainLayout1= new QGridLayout;
QGridLayout *mainLayout2= new QGridLayout;


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
    h=new double*[a];      //不确定度 协方差矩阵
    average = new double[a];
    rsd = new double[a];
    for(int i =0;i<a;i++){
        h[i] = new double[a];
        average[i]=0;
        rsd[i]=0;
    }
    for(int i =0;i<a;i++){
        for(int j =0;j<a;j++){
            h[i][j] = 0;
        }
    }

    g = new double[a];
    k = new int[a];

//    name = new string*[a];
    for(int i =0;i<a;i++){
        name[i] = new QString[a];
//        name[i]={0};
    }

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
        // qDebug()<<h[b][b]<<g[b]<<endl;
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
     // qDebug()<<i<<h[i][j+1]<<endl;
      ui->lineEdit_4->clear();
      juzhen.showme();
      //juzhen.addname();
}


void Widget::on_spinBox_2_editingFinished()         //样本数
{
    sample_Num=ui->spinBox_2->value();
    s_Result = new double *[sample_Num];
    x_sample= new double *[sample_Num];
    y_sample= new double *[sample_Num];
    x_normal= new double *[sample_Num];
    y_normal= new double *[sample_Num];
    x_uniform= new double *[sample_Num];
    y_uniform= new double *[sample_Num];
    x_exponential= new double *[sample_Num];
    y_exponential= new double *[sample_Num];
    for(int i =0;i<sample_Num;i++){
        s_Result[i] = new double[global];
        x_sample[i] = new double[global];
        y_sample[i] = new double[global];
        x_normal[i] = new double[global];
        y_normal[i] = new double[global];
        x_uniform[i] = new double[global];
        y_uniform[i] = new double[global];
        x_exponential[i] = new double[global];
        y_exponential[i] = new double[global];
//        s_Result[i] = {0};
    }
    for(int i = 0;i<sample_Num;i++){
        for(int j =0;j<global;j++){
            s_Result[i][j] = 0;
            x_sample[i][j] = 0;
            y_sample[i][j] = 0;
            x_normal[i][j] = 0;
            y_normal[i][j] = 0;
            x_uniform[i][j] = 0;
            y_uniform[i][j] = 0;
            x_exponential[i][j] = 0;
            y_exponential[i][j] = 0;
//            qDebug()<<s_Result[i][j];
        }
    }
//    qDebug()<<sizeof(s_Result);
}

void Widget::on_comboBox_4_currentIndexChanged(const QString &arg1)  //抽样方法，数字0-3对应不同抽样方法
{
    sample_M=ui->comboBox_4->currentIndex();
}

void Widget::on_pushButton_8_clicked()                          //开始抽样计算
{
         // f(h,g,sample_Num,global,sample_M,k,s_Result);         //模拟
//    qDebug()<<sample_Num-1;
    FILE *myfile;
          myfile=fopen("sample.txt","w");
          fprintf(myfile,"Final Samples are:\n");


          QFile file("D:/Qt/717.txt");
          QTextStream out(&file);
          if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
             {
                QMessageBox::warning(this,"!","can't open",QMessageBox::Yes);
             }
//          qDebug()<<sample_Num;
          sampling(h,g,sample_M,k,s_Result,sample_Num,global);
//          qDebug()<<sample_Num+1;
          for(int ii=0;ii<sample_Num;ii++)
          {
              //out<<ii+1<<"   ";
              for(int jj=0;jj<global;jj++)
              {

               double **file2;
               file2 = new double *[sample_Num];
               for(int i=0;i<sample_Num;i++){
                   file2[i] = new double[global];
               }
               for(int i = 0;i<sample_Num;i++){
                   for(int j =0;j<global;j++){
                       file2[i][j] = 0;
                   }
               }
               file2[ii][jj]=("%3e",s_Result[ii][jj]);
//                qDebug()<<ii<<" "<<jj<<"  "<<file2[ii][jj];
                fprintf(myfile," %15e",s_Result[ii][jj]);
                out<<file2[ii][jj]<<"     ";
                if(jj==global-1)
                    out<<"\n";
              }
              fprintf(myfile,"\n");
           }
           fclose(myfile);

}

void Widget::on_comboBox_5_activated(int index)
{
    ui->lineEdit_6->setText(QString::number(g[index]));

    //样本均值
    ui->lineEdit_7->setText(QString::number(average[index]));

    //均值差值
    ui->lineEdit_8->setText(QString::number(average[index]-g[index]));

    //输入不确定度
    ui->lineEdit_9->setText(QString::number(h[index][index]));

    //样本不确定度
    ui->lineEdit_10->setText(QString::number(rsd[index]));

    //不确定度差值
    ui->lineEdit_11->setText(QString::number(h[index][index]-rsd[index]));
    ks_global = index;
}

/*
void Widget::on_comboBox_5_currentIndexChanged(int index)
{
    //输入均值
    ui->lineEdit_6->setText(QString::number(g[index]));

    //样本均值
    ui->lineEdit_7->setText(QString::number(average[index]));

    //均值差值
    ui->lineEdit_8->setText(QString::number(average[index]-g[index]));

    //输入不确定度
    ui->lineEdit_9->setText(QString::number(h[index][index]));

    //样本不确定度
    ui->lineEdit_10->setText(QString::number(rsd[index]));

    //不确定度差值
    ui->lineEdit_11->setText(QString::number(h[index][index]-rsd[index]));
    ks_global = index;

    //

}
*/



void Widget::on_pushButton_9_clicked()
{
//    double *average = new double[global],*rsd = new double[global],**cc,**cov,**rcov;

    cc = new double*[global];
    cov = new double*[global];
    rcov = new double*[global];

    for(int i =0;i<global;i++){
        cc[i] = new double[global];
        cov[i] = new double[global];
        rcov[i] = new double[global];

    }
    for(int i =0;i<global;i++){
        for(int j =0;j<global;j++){
           cc[i][j] = 0;
           cov[i][j] = 0;
           rcov[i][j] = 0;
        }
    }
    //数理统计
    statistical(s_Result,average,rsd,cc,rcov,sample_Num,global);
    prob_normal = new double[global];
    prob_uni = new double[global];
    prob_expcdf = new double[global];
    for(int i = 0;i<global;i++){
        prob_expcdf[i]=0;
        prob_normal[i]=0;
        prob_uni[i]=0;
    }
    //k_s检验
    ks(s_Result,prob_normal,prob_uni,prob_expcdf);
    //累计概率密度
//    qDebug()<<340;
    CPD(s_Result,x_sample,y_sample,x_normal,y_normal,x_uniform,y_uniform,x_exponential,y_exponential);
//    qDebug()<<342;
}

void Widget::on_comboBox_6_activated(int index)
{
    //    qDebug()<<ks_global;
        //定义两个可变数组存放绘图的坐标数据
        QVector<double> x(sample_Num*global),y(sample_Num*global);//分别存放x和y坐标的数据
        combox6 = index;
        //放置显著性水平
        switch(index){
        case(0)://均匀分布

        ui->lineEdit_12->setText(QString::number(prob_uni[ks_global]));
        for(int i = 0;i<sample_Num;i++){
            for(int j=0;j<global;j++){
    //            qDebug()<<x_uniform[i][j]<<y_uniform[i][j];
                x[i*global+j] = x_uniform[i][j];
                y[i*global+j] = y_uniform[i][j];
            }
        }

            break;
        case(1)://正态分布
            ui->lineEdit_12->setText(QString::number(prob_normal[ks_global]));
            for(int i = 0;i<sample_Num;i++){
                for(int j=0;j<global;j++){
                    x[i*global+j] = x_normal[i][j];
                    y[i*global+j] = y_normal[i][j];
                }
            }
        break;

        case(2)://指数分布
            ui->lineEdit_12->setText(QString::number(prob_expcdf[ks_global]));
            for(int i = 0;i<sample_Num;i++){
                for(int j=0;j<global;j++){
                    x[i*global+j] = x_exponential[i][j];
                    y[i*global+j] = y_exponential[i][j];
                }
            }
            break;

        }
        //放置是否符合当前分布

        //绘图
    //    ui->setupUi(this);

             //添加数据，我们这里演示y=x^3,为了正负对称，我们x从-10到+10
    //        for(int i=0;i<101;i++)
    //       {
    //           x[i] = i/5 - 10;
    //           y[i] = x[i] * x[i] * x[i];
    //      }
    //        qDebug()<<1;
            //向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
            ui->qCustomPlot->addGraph();
            //添加数据
            ui->qCustomPlot->graph(0)->setData(x,y);

            //设置坐标轴标签名称
            ui->qCustomPlot->xAxis->setLabel("x");
            ui->qCustomPlot->yAxis->setLabel("y");

           //设置坐标轴显示范围,否则我们只能看到默认的范围
            ui->qCustomPlot->xAxis->setRange(-3,3);
            ui->qCustomPlot->yAxis->setRange(-1,1);

           //重绘，这里可以不用，官方例子有，执行setData函数后自动重绘
            //我认为应该用于动态显示或者是改变坐标轴范围之后的动态显示，我们以后探索
            ui->qCustomPlot->replot();
}

/*
//分布类型选择框
void Widget::on_comboBox_6_currentIndexChanged(int index)
{
//    qDebug()<<ks_global;
    //定义两个可变数组存放绘图的坐标数据
    QVector<double> x(sample_Num*global),y(sample_Num*global);//分别存放x和y坐标的数据
    combox6 = index;
    //放置显著性水平
    switch(index){
    case(0)://均匀分布

    ui->lineEdit_12->setText(QString::number(prob_uni[ks_global]));
    for(int i = 0;i<sample_Num;i++){
        for(int j=0;j<global;j++){
//            qDebug()<<x_uniform[i][j]<<y_uniform[i][j];
            x[i*global+j] = x_uniform[i][j];
            y[i*global+j] = y_uniform[i][j];
        }
    }

        break;
    case(1)://正态分布
        ui->lineEdit_12->setText(QString::number(prob_normal[ks_global]));
        for(int i = 0;i<sample_Num;i++){
            for(int j=0;j<global;j++){
                x[i*global+j] = x_normal[i][j];
                y[i*global+j] = y_normal[i][j];
            }
        }
    break;

    case(2)://指数分布
        ui->lineEdit_12->setText(QString::number(prob_expcdf[ks_global]));
        for(int i = 0;i<sample_Num;i++){
            for(int j=0;j<global;j++){
                x[i*global+j] = x_exponential[i][j];
                y[i*global+j] = y_exponential[i][j];
            }
        }
        break;

    }
    //放置是否符合当前分布

    //绘图
//    ui->setupUi(this);

         //添加数据，我们这里演示y=x^3,为了正负对称，我们x从-10到+10
//        for(int i=0;i<101;i++)
//       {
//           x[i] = i/5 - 10;
//           y[i] = x[i] * x[i] * x[i];
//      }
//        qDebug()<<1;
        //向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        ui->qCustomPlot->addGraph();
        //添加数据
        ui->qCustomPlot->graph(0)->setData(x,y);

        //设置坐标轴标签名称
        ui->qCustomPlot->xAxis->setLabel("x");
        ui->qCustomPlot->yAxis->setLabel("y");

       //设置坐标轴显示范围,否则我们只能看到默认的范围
        ui->qCustomPlot->xAxis->setRange(-3,3);
        ui->qCustomPlot->yAxis->setRange(-1,1);

       //重绘，这里可以不用，官方例子有，执行setData函数后自动重绘
        //我认为应该用于动态显示或者是改变坐标轴范围之后的动态显示，我们以后探索
        ui->qCustomPlot->replot();

}
*/

void Widget::on_tabWidget_2_currentChanged(int index)
{
//    Qwidget* myWidget = new QWidget();

////    ...    // 对窗口做相应的操作，例如新建自己的Layout取名叫myLayout

//    myWidget->setLayout(myLayout);

//    setCentralWidget(myWidget);
//if(number_gruop3 ==0||number_gruop4 ==0||number_gruop5 ==0){

    double zz[9][9]=
    {
       {1.000000, 0.309607, -0.763380,  -0.150282,  -0.656015,  0.051649,  0.771892,  0.174455 , -0.016790},
       { 0.309607, 1.000000 , -0.002989 , 0.015329,  -0.005206 , 0.155284 , 0.001872 , 0.400282  ,0.006105},
       { -0.763380,  -0.002989,  1.000000 , 0.289071,  0.751140,  -0.084338 , -0.930787 , -0.210328 , 0.057080},
       {-0.150282, 0.015329,  0.289071,  1.000000,  0.090726  -0.144011  -0.165986  -0.811375  -0.028247},
       {-0.656015, -0.005206 , 0.751140,  0.090726,  1.000000,  -0.000428,  -0.855364,  -0.001752,  0.070402},
       {0.051649,  0.155284,  -0.084338,  -0.144011,  -0.000428,  1.000000,  0.027322,  0.217830,  -0.106959},
       {0.771892,  0.001872,  -0.930787,  -0.165986 , -0.855364,  0.027322,  1.000000,  0.028479,  -0.048922},
       {0.174455,  0.400282,  -0.210328,  -0.811375 , -0.001752,  0.217830,  0.028479,  1.000000,  0.007008},
       {-0.016790,  0.006105,  0.057080,  -0.028247 , 0.070402,  -0.106959,  -0.048922,  0.007008,  1.000000}
     };

    QStringList list;
    for(int i=9;i>0;i--)
        list<<QString::number(i);
    QStringList list2;
    for(int j=1;j<10;j++)
        list2<<QString::number(j);



    switch(index)
   {

    case 0:
      {
        bar->scene()->activeCamera()->setCameraPosition(50,50,150);//角度
        bar->activeTheme()->setLabelBackgroundEnabled(false);
        bar->activeTheme()->setBackgroundEnabled(false);
        bar->activeTheme()->setGridLineColor("red");

        QWidget *container = QWidget::createWindowContainer(bar);
        container->setMaximumSize(500,500);

        QValue3DAxis *z=new QValue3DAxis();                                                 //z轴
        z->setTitle("Correlation Coefficient");                                            //title
        z->setTitleVisible(true);
        z->setSegmentCount(4);                                                             //z轴分为4段
        z->setRange(-1,1);                                                                //range
        z->setLabelFormat(QString(QStringLiteral("%.6f")));                              //数据格式


        QCategory3DAxis *x=new QCategory3DAxis();
        QCategory3DAxis *y=new QCategory3DAxis();

        bar->setValueAxis(z);
        bar->setRowAxis(y);
        bar->setColumnAxis(x);                                                          //加入x,y,z轴

       QBar3DSeries *serise=new QBar3DSeries();                                        //直方柱
       serise->setBaseColor(QColor(200,100,200,200));
       bar->addSeries(serise);

       QBarDataArray *dataSet = new QBarDataArray;
       QBarDataRow *dataRow;
       dataSet->reserve(list.size());                                                  //??

       //int num=list.size();

       for(int m=(list.size())-1;m>=0;m--)
       {
           dataRow = new QBarDataRow(list.size());


           //int hh=8;
           for(int n=0;n<list.size();n++)
           {
               (*dataRow)[n].setValue(zz[n][m]*2);
              // hh--;

           }
           dataSet->append(dataRow);
       }

       serise->dataProxy()->resetArray(dataSet,list,list2);
       bar->show();


        if(number_gruop3==1)
        {
            qDebug()<<"mmmmmmmmmmm";
            bar->removeSeries(serise);
            QLayoutItem *child;
           while(child=ui->groupBox_3->layout()->takeAt(0))
              delete child;
          // mainLayout->deleteLater();
           // ui->groupBox_3->setLayout(mainLayout);
         }
        ui->groupBox_3->setLayout(mainLayout0);
        mainLayout0->addWidget(container);
        number_gruop3=1;
        break;
      }
    case 1:
       {
        bar1->scene()->activeCamera()->setCameraPosition(50,50,150);//角度
        bar1->activeTheme()->setLabelBackgroundEnabled(false);
        bar1->activeTheme()->setBackgroundEnabled(false);
        bar1->activeTheme()->setGridLineColor("red");

       QWidget *container1 = QWidget::createWindowContainer(bar1);
        container1->setMaximumSize(500,500);
       // QGridLayout *mainLayout1= new QGridLayout;

        QValue3DAxis *z1=new QValue3DAxis();                                                 //z轴
        z1->setTitle("Correlation Coefficient");                                            //title
        z1->setTitleVisible(true);
        z1->setSegmentCount(4);                                                             //z轴分为4段
        z1->setRange(-1,1);                                                                //range
        z1->setLabelFormat(QString(QStringLiteral("%.6f")));                              //数据格式


        QCategory3DAxis *x1=new QCategory3DAxis();
        QCategory3DAxis *y1=new QCategory3DAxis();

        bar1->setValueAxis(z1);
        bar1->setRowAxis(y1);
        bar1->setColumnAxis(x1);                                                          //加入x,y,z轴

       QBar3DSeries *serise1=new QBar3DSeries();                                        //直方柱
       serise1->setBaseColor(QColor(200,100,200,200));
       bar1->addSeries(serise1);

       QBarDataArray *dataSet1 = new QBarDataArray;
       QBarDataRow *dataRow1;
       dataSet1->reserve(list.size());                                                  //??

       //int num=list.size();

       for(int m=(list.size())-1;m>=0;m--)
       {
           dataRow1 = new QBarDataRow(list.size());
           //int hh=8;
           for(int n=0;n<list.size();n++)
           {
               (*dataRow1)[n].setValue(zz[n][m]);
              // hh--;

           }
           dataSet1->append(dataRow1);
       }

       serise1->dataProxy()->resetArray(dataSet1,list,list2);
       bar1->show();
        if(number_gruop4==1)
        {
            bar1->removeSeries(serise1);
            QLayoutItem *child1;
           while(child1=ui->groupBox_4->layout()->takeAt(0))
              delete child1;

            //ui->groupBox_4->setLayout(mainLayout1);

        }
        ui->groupBox_4->setLayout(mainLayout1);
        mainLayout1->addWidget(container1);
        number_gruop4=1;
        break;
      }

    case 2:
       {
        bar2->scene()->activeCamera()->setCameraPosition(50,50,150);//角度
        bar2->activeTheme()->setLabelBackgroundEnabled(false);
        bar2->activeTheme()->setBackgroundEnabled(false);
        bar2->activeTheme()->setGridLineColor("red");

       QWidget *container2 = QWidget::createWindowContainer(bar2);
        container2->setMaximumSize(500,500);
       // QGridLayout *mainLayout2= new QGridLayout;
        QValue3DAxis *z2=new QValue3DAxis();                                                 //z轴
        z2->setTitle("Correlation Coefficient");                                            //title
        z2->setTitleVisible(true);
        z2->setSegmentCount(4);                                                             //z轴分为4段
        z2->setRange(-1,1);                                                                //range
        z2->setLabelFormat(QString(QStringLiteral("%.6f")));                              //数据格式


        QCategory3DAxis *x2=new QCategory3DAxis();
        QCategory3DAxis *y2=new QCategory3DAxis();

        bar2->setValueAxis(z2);
        bar2->setRowAxis(y2);
        bar2->setColumnAxis(x2);                                                          //加入x,y,z轴

       QBar3DSeries *serise2=new QBar3DSeries();                                        //直方柱
       serise2->setBaseColor(QColor(200,100,200,200));
       bar2->addSeries(serise2);

       QBarDataArray *dataSet2 = new QBarDataArray;
       QBarDataRow *dataRow2;
       dataSet2->reserve(list.size());                                                  //??

       //int num=list.size();

       for(int m=(list.size())-1;m>=0;m--)
       {
           dataRow2 = new QBarDataRow(list.size());


           //int hh=8;
           for(int n=0;n<list.size();n++)
           {
               (*dataRow2)[n].setValue(zz[n][m]);
              // hh--;

           }
           dataSet2->append(dataRow2);
       }

       serise2->dataProxy()->resetArray(dataSet2,list,list2);
       bar2->show();

        if(number_gruop5==1)
        {
            bar2->removeSeries(serise2);
            QLayoutItem *child2;
            while(child2=ui->groupBox_5->layout()->takeAt(0))
               delete child2;
           // mainLayout2->deleteLater();
           // ui->groupBox_5->setLayout(mainLayout2);

        }
         ui->groupBox_5->setLayout(mainLayout2);
         mainLayout2->addWidget(container2);
          number_gruop5=1;
        break;
      }

  //  }

   qDebug()<<number_gruop3<<number_gruop4<<number_gruop5<<index;

}


}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    xx=position;
    bar->scene()->activeCamera()->setCameraPosition(xx,yy,150);
    bar1->scene()->activeCamera()->setCameraPosition(xx,yy,150);
    bar2->scene()->activeCamera()->setCameraPosition(xx,yy,150);
}

void Widget::on_horizontalSlider_2_sliderMoved(int position)
{
    yy=position;
    bar->scene()->activeCamera()->setCameraPosition(xx,yy,150);
    bar1->scene()->activeCamera()->setCameraPosition(xx,yy,150);
    bar2->scene()->activeCamera()->setCameraPosition(xx,yy,150);
}

void Widget::on_pushButton_10_clicked()
{
     ui->tabWidget->setCurrentIndex(4);

}


