#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QFileDialog"
#include"opencv2/opencv.hpp"
#include<highgui.h>
#include<QImage>
#include"cv.h"
#include<QTimer>
#include<QDebug>
#include<QPixmap>


using namespace cv;
using namespace std;

//本地图片定义
Mat localimage;
//cv::cvtColor(localimage,localimage,CV_BGR2RGB);
QImage localimg;
QString fileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


QImage  Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;

}

void MainWindow::nextFrame()
{
    capture >> frame;
    if (!frame.empty())
    {
        image = Mat2QImage(frame);
        QGraphicsScene *scene = new QGraphicsScene;
        scene->addPixmap(QPixmap::fromImage(image));
        ui->graphicsView->setScene(scene);
        //ui->graphicsView->adjustSize();
        ui->graphicsView->update();
        ui->graphicsView->show();

   }
}

void MainWindow::on_pushButton_5_clicked()                      //打开相机  参考：https://www.cnblogs.com/annt/p/ant003.html#3872827
{
    if(capture.isOpened())
        capture.release();

    capture.open(0);
    if(capture.isOpened())
    {
//        rate=capture.get(CV_CAP_PROP_FPS);
//        qDebug()<<rate;           //0
        capture>>frame;
        if(!frame.empty())
        {
            image=Mat2QImage(frame);
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(image));
            ui->graphicsView->setScene(scene);
           // ui->graphicsView->adjustSize();
            ui->graphicsView->show();

            timer = new QTimer(this);
            timer->setInterval(50);                                         //set timer match with FPS
            connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            timer->start();
          }
    }


}


void MainWindow::on_pushButton_3_clicked()     //打开本地图片                                //打开本地图片
{
    if(capture.isOpened())                                                //判断摄像头是否打开，若打开，则先关闭，否则会崩溃
        capture.release();

    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    localimage = cv::imread(fileName.toLatin1().data());
    cv::cvtColor(localimage,localimage,CV_BGR2RGB);
    localimg = QImage((const unsigned char*)(localimage.data),localimage.cols,localimage.rows,QImage::Format_RGB888);
    ui->graphicsView->resize(localimg.width(), localimg.height());
    ui->graphicsView_2->resize(localimg.width(), localimg.height());
    QGraphicsScene *scene = new QGraphicsScene;
        //scene->setSceneRect(0,0,img.width(),img.height());
    scene->addPixmap(QPixmap::fromImage(localimg));
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView->adjustSize();
    ui->graphicsView_2->adjustSize();
    ui->graphicsView->show();
    ui->graphicsView_2->show();
}

//void MainWindow::on_pushButton_4_clicked()   //亮度
//{
//    pPixmap=new QPixmap(fileName);
//    QImage  image=pPixmap->toImage();
//    unsigned char *pData=image.bits();

//        int width=image.width();
//        int height=image.height();

//        for(int i=0;i<height;i++)
//        {
//               for(int j=0;j<width;j++)
//               {
//                    *(pData+(i*width+j)*4)=150;      //B
//                    *(pData+(i*width+j)*4+1)=150;    //G
//                    *(pData+(i*width+j)*4+2)=150;    //R
//               }
//        }
//     QPixmap ConvertPixmap=QPixmap::fromImage(image);
//     QGraphicsScene *scene = new QGraphicsScene;
//     //scene->setSceneRect(0,0,img.width(),img.height());
//     scene->addPixmap(ConvertPixmap);

//     ui->graphicsView_2->setScene(scene);
//     ui->graphicsView_2->adjustSize();
//     ui->graphicsView_2->show();
//}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    pPixmap=new QPixmap(fileName);
    QImage  image=pPixmap->toImage();
       unsigned char *pData=image.bits();

       int width=image.width();
       int height=image.height();

       for(int i=0;i<height;i++)
       {
              for(int j=0;j<width;j++)
              {
                   *(pData+(i*width+j)*4)=(*(pData+(i*width+j)*4)*value*3/255);
                   *(pData+(i*width+j)*4+1)=(*(pData+(i*width+j)*4+1)*value*3/255);
                   *(pData+(i*width+j)*4+2)=(*(pData+(i*width+j)*4+2)*value*3/255);
              }
       }
       QPixmap ConvertPixmap=QPixmap::fromImage(image);
       QGraphicsScene *scene = new QGraphicsScene;
       scene->setSceneRect(0,0,image.width(),image.height());
       scene->addPixmap(ConvertPixmap);
       ui->graphicsView_2->setScene(scene);
      // ui->graphicsView_2->adjustSize();
       ui->graphicsView_2->show();
}
