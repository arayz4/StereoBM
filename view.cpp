#include "view.h"

#include <QMainWindow>

View::View(QWidget *parent) : QWidget(parent)
{
    yomi = false;

    imgLeft = NULL;
    imgRight = NULL;

    intsld1 = 16;
    intsld2 = 21;
    intsld3 = 5;
}

void View::loadimg(QStringList list)
{
    if(list.size() != 2)
        return;

    QString str1 = list.at(0);
    QString str2 = list.at(1);
    cv::String cvpath1(str1.toStdString());
    cv::String cvpath2(str2.toStdString());

    imgLeft = imread( cvpath1, IMREAD_GRAYSCALE );
    imgRight = imread( cvpath2, IMREAD_GRAYSCALE );

    imgDisparity16S = Mat( imgLeft.rows, imgLeft.cols, CV_16S );
    imgDisparity8U = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

    stereobm();
}

void View::stereobm()
{
    //FILTER for STEREOBM

    int ndisparities = intsld1*intsld3;
    int SADWindowSize = intsld2;
    Ptr<StereoBM> sbm = StereoBM::create( ndisparities, SADWindowSize );

    //-- 3. Calculate the disparity image
    sbm->compute( imgLeft, imgRight, imgDisparity16S );

    //-- Check its extreme values
    double minVal; double maxVal;
    minMaxLoc( imgDisparity16S, &minVal, &maxVal );

    //qDebug() << "min: " << minVal << " / max: " << maxVal;

    //-- 4. Display it as a CV_8UC1 image
    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    qtimage = QImage( imgDisparity8U.data, imgDisparity8U.cols, imgDisparity8U.rows,  QImage::Format_RGB888);

    yomi = true;
}

void View::paintEvent(QPaintEvent *)
{
    if(yomi){
        QPainter paint;
        paint.begin(this);
        if(!qtimage.isNull()){
            paint.drawImage(0,0,qtimage);
        }
        paint.end();
    }
}
