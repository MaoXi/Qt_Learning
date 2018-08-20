#ifndef SHOW_H
#define SHOW_H

#endif // SHOW_H
#include <QWidget>
#include"ui_juzhen.h"

class Juzhen : public QWidget,public Ui::Juzhen
{
   Q_OBJECT

public:
    //explicit
    Juzhen(QWidget *parent = 0);
    ~Juzhen();
    void showme();
   // void addname();

protected:
    void changeEvent(QEvent *e);


private slots:


    void on_pushButton_clicked();

private:
    Ui::Juzhen *ui;

};

//#endif // WIDGET_H
