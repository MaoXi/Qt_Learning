#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"form.h"

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

private:
    Ui::Widget *ui;
    Form form;
};

#endif // WIDGET_H
