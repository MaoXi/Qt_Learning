#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QFileDialog"
#include"opencv2/opencv.hpp"
#include"cv.h"
#include<QTimer>


using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    this->resize(800,600);
//    cv::Mat image=cv::imread("D:\\dowmload_\\Chrome download\\picture\\0.jpg",1);
//    cv::namedWindow("myimg");
//    cv::imshow("myimg",image);
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

void MainWindow::on_pushButton_clicked()
{/*
     QString filename=QFileDialog::getOpenFileName(this,"open","/","imgfiles(*.bpm *.jpg *.png)");
    //Mat src1=imread("D:\\dowmload_\\Chrome download\\picture\\0.jpg");
    String name=filename.toStdString();
     Mat src1=imread(name);
     cvtColor(src1,src1,CV_BGR2RGB);
    QImage showImage((const uchar*)src1.data,src1.cols,src1.rows,src1.cols*src1.channels(),QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(showImage));*/
}

void MainWindow::on_pushButton_5_clicked()
{
//    bool start = true;
//    Mat frame;
//    QImage TakeP;
//    VideoCapture cap;
//    QImage Mat2Qimage(Mat& mat);
//    QTimer *timer;
//       while(start)
//       {
//           cap>>frame;
//           imshow("Camera",frame);
//           waitKey(10);
//           timer->start(50);
//           QImage img = Mat2Qimage(frame);
//           //Canny(frame,CannyImg,100,255);
//           //QImage img1 = Mat2Qimage(CannyImg);
//           TakeP = img;
//           ui->label->setPixmap(QPixmap::fromImage(img));
//           //ui.label1->setPixMap(QPixmap::fromImage(img1));
//           //ui.label_1->setPixmap(QPixmap::fromImage(img1));
//           //ui.label->setScaledContents(true);
//           int c = waitKey(30);
//           if(c>=0)
//           {
//               waitKey(0);
//           }
//       }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
    Mat image = cv::imread(fileName.toLatin1().data());
    cv::cvtColor(image,image,CV_BGR2RGB);
    QImage img = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    ui->graphicsView->resize(img.width(), img.height());
    QGraphicsScene *scene = new QGraphicsScene;
        //scene->setSceneRect(0,0,img.width(),img.height());
    scene->addPixmap(QPixmap::fromImage(img));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->adjustSize();
    ui->graphicsView->show();
}
