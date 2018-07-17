#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGridLayout>
#include<QPushButton>
#include<QLineEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QGridLayout * mainLayout= new QGridLayout(ui->groupBox);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool MainWindow::on_pushButton_2_clicked( )
{
    return false;
}



void MainWindow::on_pushButton_clicked()
{
   QGridLayout * mainLayout= new QGridLayout(ui->groupBox);
       QPushButton *tl[100];
       int a=ui->spinBox->value();

       for(int i=0;i<a;i++)
  {

    for(int j=0;j<a;j++)
    {
        tl[j]=new QPushButton(ui->groupBox);
        tl[j]->setMaximumSize(700/a,700/a);
        tl[j]->setText(QString::number(i*a+1+j));
        tl[j]->setToolTip(QString::number(i+1)+u8"行"+QString::number(j+1)+u8"列");
        if(i==j)
            tl[j]->setStyleSheet("color:red");
        mainLayout->addWidget(tl[j], i, j);
     }
   }
        mainLayout->setMargin(0);
        mainLayout->setSpacing(0);


}




