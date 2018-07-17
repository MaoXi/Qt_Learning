#include"form.h"
#include"QFileDialog"
Form::Form(QWidget *parent) : QWidget(parent)

{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::changeEvent(QEvent *e)
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

void Form::on_pushButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,"open","/","files(*)");
    ui->lineEdit->setText(filename);
}

void Form::on_pushButton_2_clicked()
{
   this->close();
    ui->lineEdit->clear();
   // tabWidget->setCurrentIndex(2);
}
