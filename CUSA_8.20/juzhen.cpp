#include"juzhen.h"
#include"QGridLayout"
#include"QPushButton"
#include"QLayoutItem"

extern int global;
extern double **h;
extern QString *name[1000];
QGridLayout *mainLayout= new QGridLayout;
QPushButton *tl[100];
Juzhen::Juzhen(QWidget *parent):
    QWidget(parent),
     ui(new Ui::Juzhen)

{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

}

Juzhen::~Juzhen()
{
    delete ui;
}

void Juzhen::changeEvent(QEvent *e)
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

void Juzhen::showme()
{
    ui->lineEdit->setText(QString::number(global));

    QString a1=ui->lineEdit->text();
    int a=a1.toInt();
    ui->lineEdit->hide();
    //QGridLayout *mainLayout= new QGridLayout(ui->groupBox);
    ui->groupBox->setLayout(mainLayout);
    //QPushButton *tl[100];

        for(int i=0;i<a;i++)
   {

     for(int j=0;j<a;j++)
     {
         tl[j]=new QPushButton;   //(ui->groupBox);
         tl[j]->setMaximumSize(700/a,700/a);
        // tl[j]->setText(QString::number(i*a+1+j));
         tl[j]->setToolTip(QString::number(i+1)+u8"行"+QString::number(j+1)+u8"列"+"\n"+name[i][j]);
         if(i==j)
            {

             tl[j]->setStyleSheet("color:red");
             tl[j]->setText(QString::number(h[i][j],'%15e',5));
            }
         else tl[j]->setText(QString::number(h[i][j],'%15e',5));
         mainLayout->addWidget(tl[j], i, j);
      }
    }
         mainLayout->setMargin(0);
         mainLayout->setSpacing(0);
}
/*
void Juzhen::addname()
{
    ui->lineEdit->setText(QString::number(global));
    QString a1=ui->lineEdit->text();
    int a=a1.toInt();
    for(int m=0;m<a;m++)
    {
        for(int n=0;n<a;n++)
        {
            if(m==n)
               {

                tl[n]->setStyleSheet("color:red");
                tl[n]->setText(u8"不确定"+QString::number(h[m][n]));
               }
            else tl[n]->setText(u8"协方差"+QString::number(h[m][n]));
        }
    }
}
*/


void Juzhen::on_pushButton_clicked()
{
     QLayoutItem *child;
    while(child=this->ui->groupBox->layout()->takeAt(0))
        delete child;
    this->close();
}
