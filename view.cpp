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

void View::stereobm()
{
    if (!yomi){
        QStringList filenam;

        filenam = QFileDialog::getOpenFileNames(this, tr("Open Image"), ".",tr("Image file (*.jpg *.jpeg *.png *bmp)"));
        QString str1 = filenam.at(0);
        QString str2 = filenam.at(1);
        cv::String cvpath1(str1.toStdString());
        cv::String cvpath2(str2.toStdString());

        imgLeft = imread( cvpath1, IMREAD_GRAYSCALE );
        imgRight = imread( cvpath2, IMREAD_GRAYSCALE );

        imgDisparity16S = Mat( imgLeft.rows, imgLeft.cols, CV_16S );
        imgDisparity8U = Mat( imgLeft.rows, imgLeft.cols, CV_8UC1 );

        yomi = true;
    }

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

    //qtimage = QImage( imgDisparity16S.data, imgDisparity16S.cols, imgDisparity16S.rows,  QImage::Format_RGB888);

    namedWindow( "windowDisparity", WINDOW_NORMAL );
    imshow( "windowDisparity", imgDisparity8U );

}

void View::paintEvent(QPaintEvent *)
{
    /*if(yomi){
        QPainter paint;
        paint.begin(this);
        if(!qtimage.isNull()){
            paint.drawImage(0,0,qtimage);
        }
        paint.end();
    }*/
}
