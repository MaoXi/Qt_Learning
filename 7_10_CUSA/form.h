#ifndef FORM_H
#define FORM_H

#endif // FORM_H

#include <QWidget>
#include"ui_form.h"
/*
namespace Ui {
class Form;
}
*/
class Form : public QWidget,public Ui::Form
{
   Q_OBJECT

public:
    //explicit
    Form(QWidget *parent = 0);
    ~Form();

protected:
    void changeEvent(QEvent *e);

private slots:


    void on_pushButton_clicked();

private:
    Ui::Form *ui;
};

//#endif // WIDGET_H
