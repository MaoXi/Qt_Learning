#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    QWidget *widget1 = new QWidget;
    ui->tabWidget->addTab(widget1,"test");
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

    ui->comboBox->clear();
    for(int i=1;i<=a;i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }
}
