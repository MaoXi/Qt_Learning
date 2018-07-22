#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtDataVisualization/Q3DBars.h>

using namespace QtDataVisualization;



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
    int xx;
    int yy;

protected:
    void changeEvent(QEvent *e);

private slots:


    void on_horizontalSlider_sliderMoved(int positionx);

    void on_horizontalSlider_2_sliderMoved(int positiony);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
