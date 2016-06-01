//view.cpp
//date : 2016/06/01
//auther : Shunsuke Izumi
//discription : To display image with openCV stereoBM function

#include "view.h"
#include "mainwindow.h"

#include <QMainWindow>

View::View(QWidget *parent) : QWidget(parent)
{
    l_screen = new QLabel;
    l_screen->setAlignment(Qt::AlignCenter);
    lay_screen = new QHBoxLayout;
    this->setLayout(lay_screen);
    lay_screen->addWidget(l_screen);
    l_screen->setPixmap(pix);

    imgLeft = NULL;
    imgRight = NULL;

    intsld1 = 16;
    intsld2 = 21;
    intsld3 = 5;

    imageloaded = false;
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

    imageloaded = true;

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

    //-- 4. Display it as a CV_8UC1 image
    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    pix = QPixmap::fromImage(QImage((unsigned char*) imgDisparity8U.data, imgDisparity8U.cols, imgDisparity8U.rows, QImage::Format_Grayscale8));

    p_main->slot_zoom();
}

QPixmap View::pixmap_sizemodify(QPixmap pix){//Might we don't use this function
    if(pix.isNull()){
        return QPixmap();
    }

    int size_w = pix.width();
    int size_h = pix.height();

    int thre_max_w = 1500;
    int thre_max_h = 900;
    QPixmap tmp;
    if ( size_w > thre_max_w || size_h > thre_max_h){
        int size_resize_w, size_resize_h;
        size_resize_w = thre_max_w / 2;
        size_resize_h = thre_max_h / 2;
        tmp = pix.scaled(size_resize_w,size_resize_h,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        return tmp;
    }else{
        return pix;
    }
}

void View::pixmap_scale(int zoom){
    int width,height;
    width = pix.width();
    height = pix.height();

    double zoomval = (double)zoom / (double)100;

    double scaled_w, scaled_h;

    scaled_w = (double)width * zoomval;
    scaled_h = (double)height * zoomval;

    l_screen->setPixmap(pix.scaled((int)scaled_w, (int)scaled_h,Qt::IgnoreAspectRatio,Qt::FastTransformation));
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
