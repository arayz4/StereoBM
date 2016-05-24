#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT
#include <QMainWindow>
#include <QtGui>
#include <QImage>

//OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


//GUI
#include <QSpinBox>
#include <QVBoxLayout>

using namespace std;
using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    QImage* IplImage2QImage(const IplImage *iplImg);

    void stereoma();

    bool showimg;

    bool bla;

    //webcam
    CvCapture* capture;

    IplImage* iplimg;

    //GUI
    QSpinBox *sld1;
    QSpinBox *sld2;
    QSpinBox *sld3;

    QWidget *mainwid;
    QVBoxLayout *vlay;

    //Disparity
    Mat imgLeft;
    Mat imgRight;
    Mat imgDisparity16S;
    Mat imgDisparity8U;

    bool yomi;

public slots:
    void slid();

private:
    QImage* qtimage;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent* ev);
};

#endif // MAINWINDOW_H
