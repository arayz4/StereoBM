#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

#include <QFileDialog>
#include <QtGui>
#include <QPainter>

//OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class MainWindow;
class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

    MainWindow *p_main;
    void stereobm();

    bool yomi;

    QImage* IplImage2QImage(const IplImage *iplImg);

    QImage qtimage;

    //Disparity
    Mat imgLeft;
    Mat imgRight;
    Mat imgDisparity16S;
    Mat imgDisparity8U;

    //parameter
    int intsld1;
    int intsld2;
    int intsld3;

    //MainWindow *p_main;

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // VIEW_H
