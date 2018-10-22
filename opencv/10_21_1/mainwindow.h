#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cv.h"
#include "highgui.h"
#include <QTime>
#include<opencv.hpp>
#include<QPixmap>
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();
     void nextFrame();

 //    void on_pushButton_4_clicked();

     void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    cv::Mat frame;
        cv::VideoCapture capture;
        QImage  image;
        QTimer *timer;
        double rate; //FPS
        cv::VideoWriter writer;   //make a video record
        QPixmap *pPixmap;

};

#endif // MAINWINDOW_H
