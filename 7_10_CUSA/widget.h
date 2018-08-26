#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"form.h"
#include"juzhen.h"
#include<QtDataVisualization/Q3DBars.h>

using namespace QtDataVisualization;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Q3DBars *bar=new Q3DBars();
    Q3DBars *bar1=new Q3DBars();
    Q3DBars *bar2=new Q3DBars();
    int xx=50;
    int yy=50;


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

    void on_spinBox_2_editingFinished();

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_pushButton_8_clicked();



  //  void on_comboBox_5_currentIndexChanged(int index);

    void on_pushButton_9_clicked();





   // void on_comboBox_6_currentIndexChanged(int index);

    void on_tabWidget_2_currentChanged(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);



    void on_comboBox_5_activated(int index);

    void on_comboBox_6_activated(int index);

    void on_pushButton_10_clicked();




    void on_pushButton_12_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::Widget *ui;
    Form form;
    Juzhen juzhen;
};

#endif // WIDGET_H
