#include "widget.h"
#include "ui_widget.h"
#include"qcustomplot.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //定义两个可变数组存放绘图的坐标数据
        QVector<double> x(101),y(101);//分别存放x和y坐标的数据,101为数据长度
         //添加数据，我们这里演示y=x^3,为了正负对称，我们x从-10到+10
        for(int i=0;i<101;i++)
        {
            x[i] = i/5 - 10;
            y[i] = x[i] * x[i] * x[i];
       }

        //向绘图区域QCustomPlot(从widget提升来的)添加一条曲线
        ui->qCustomPlot->addGraph();
        //添加数据
        ui->qCustomPlot->graph(0)->setData(x,y);

        //设置坐标轴标签名称
        ui->qCustomPlot->xAxis->setLabel("x");
        ui->qCustomPlot->yAxis->setLabel("y");

       //设置坐标轴显示范围,否则我们只能看到默认的范围
        ui->qCustomPlot->xAxis->setRange(-11,11);
        ui->qCustomPlot->yAxis->setRange(-1100,1100);

       //重绘，这里可以不用，官方例子有，执行setData函数后自动重绘
        //我认为应该用于动态显示或者是改变坐标轴范围之后的动态显示，我们以后探索
       //ui->qCustomPlot->replot();
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
