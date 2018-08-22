#include "widget.h"
#include "ui_widget.h"
#include<QDir>
#include<QListWidgetItem>
#include<QDebug>

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

void Widget::on_pushButton_clicked()
{
    QDir dir("D:/dowmload_/Chrome download/picture");

    QFileInfoList list=dir.entryInfoList();
    for(int i=0;i<list.size();++i)
    {
        QFileInfo info=list.at(i);
        QListWidgetItem *newItem=new QListWidgetItem();
        newItem->setText(info.fileName());
        ui->listWidget->addItem(newItem);
    }

}

void Widget::on_listWidget_currentRowChanged(int currentRow)
{
    qDebug()<<currentRow;
}

void Widget::on_pushButton_2_clicked()
{
   // QListWidgetItem *item=ui->listWidget->takeItem(ui->listWidget->currentRow());
   // ui->listWidget_2->addItem(item);
   // delete item;
    QList <QListWidgetItem*> item;
    item=ui->listWidget->selectedItems();
    for(int j=0;j<item.size();j++)
    {
        QListWidgetItem *item0=item[j];
        int r=ui->listWidget->row(item0);
        ui->listWidget->takeItem(r);
        ui->listWidget_2->addItem(item0);
    }

}

void Widget::on_pushButton_3_clicked()
{
    QList <QListWidgetItem*> item2;
    item2=ui->listWidget_2->selectedItems();
    for(int k=0;k<item2.size();k++)
    {
        QListWidgetItem *item3=item2[k];
        int r2=ui->listWidget_2->row(item3);
        ui->listWidget_2->takeItem(r2);
        ui->listWidget->addItem(item3);
    }
}

void Widget::on_pushButton_4_clicked()
{
    int r3=0;
    QString text0;
    while(r3<(ui->listWidget_2->count()))
    {
        text0=ui->listWidget_2->item(r3)->text();
        r3++;
        qDebug()<<text0;
    }
}
