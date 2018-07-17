#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"form.h"
#include"juzhen.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_2_clicked();



    void on_spinBox_editingFinished();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();


    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    Form form;
    Juzhen juzhen;
};

#endif // WIDGET_H
