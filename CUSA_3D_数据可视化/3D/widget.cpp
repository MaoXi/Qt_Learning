#include "widget.h"
#include "ui_widget.h"
#include<QtDataVisualization/Q3DBars.h>
#include<QGridLayout>
#include<QColor>
#include<QColormap>

using namespace QtDataVisualization;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
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

    //Q3DBars *bar=new Q3DBars();
    bar->scene()->activeCamera()->setCameraPosition(50,50,150);//角度
    bar->activeTheme()->setLabelBackgroundEnabled(false);
    bar->activeTheme()->setBackgroundEnabled(false);

    QWidget *container = QWidget::createWindowContainer(bar);
    container->setMaximumSize(450,450);
    QGridLayout *mainLayout= new QGridLayout;
    ui->groupBox->setLayout(mainLayout);
    mainLayout->addWidget(container);


    QValue3DAxis *z=new QValue3DAxis();                  //z轴
    z->setTitle("Correlation Coefficient");               //title
    z->setTitleVisible(true);
    z->setSegmentCount(4);                               //z轴分为4段
    z->setRange(-1,1);                                    //range
    z->setLabelFormat(QString(QStringLiteral("%.6f")));   //数据格式


    QCategory3DAxis *x=new QCategory3DAxis();
    QCategory3DAxis *y=new QCategory3DAxis();

    bar->setValueAxis(z);
    bar->setRowAxis(y);
    bar->setColumnAxis(x);                          //加入x,y,z轴

   QBar3DSeries *serise=new QBar3DSeries();        //直方柱
   serise->setBaseColor(QColor(200,100,200,200));
   bar->addSeries(serise);                         //加入柱子

   QBarDataArray *dataSet = new QBarDataArray;
   QBarDataRow *dataRow;
   dataSet->reserve(list.size());            //??

   //int num=list.size();

   for(int m=(list.size())-1;m>=0;m--)
   {
       dataRow = new QBarDataRow(list.size());


       //int hh=8;
       for(int n=0;n<list.size();n++)
       {
           (*dataRow)[n].setValue(zz[n][m]);
          // hh--;

       }
       dataSet->append(dataRow);
   }

   serise->dataProxy()->resetArray(dataSet,list,list2);
   bar->show();

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




void Widget::on_horizontalSlider_sliderMoved(int positionx)
{
      xx=positionx;
      bar->scene()->activeCamera()->setCameraPosition(xx,yy,150);
}

void Widget::on_horizontalSlider_2_sliderMoved(int positiony)
{
      yy=positiony;
      bar->scene()->activeCamera()->setCameraPosition(xx,yy,150);
}
