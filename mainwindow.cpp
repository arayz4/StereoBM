#include "mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    showimg = false;
    bla = true;

    imgLeft = NULL;
    imgRight = NULL;

    sld1 = new QSpinBox();
    sld2 = new QSpinBox();
    sld3 = new QSpinBox();

    yomi = false;

    mainwid = new QWidget;
    vlay = new QVBoxLayout;
    this->setCentralWidget(mainwid);
    mainwid->setLayout(vlay);
    vlay->addWidget(sld1);
    vlay->addWidget(sld3);
    vlay->addSpacing(50);
    vlay->addWidget(sld2);

    sld1->setValue(16);
    sld1->setSingleStep(16);
    sld1->setRange(0,160);

    sld2->setValue(21);
    sld2->setRange(5,255);
    sld2->setSingleStep(2);

    sld3->setValue(5);
    sld3->setRange(1,25);
    sld3->setSingleStep(1);

    QObject::connect(sld1,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(sld2,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(sld3,SIGNAL(valueChanged(int)),this,SLOT(slid()));

}

void MainWindow::slid()
{
    stereoma();
}

// IplImage から QImage に変換
QImage* MainWindow::IplImage2QImage(const IplImage *iplImg)
{
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1)
            {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4)
            {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4)
            {
                a = data[x * channels + 3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else
            {
                qimg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qimg;
}

void MainWindow::stereoma()
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

    //-- 2. Call the constructor for StereoBM
    int intsld1 = sld1->value();
    int intsld2 = sld2->value();
    int intsld3 = sld3->value();

    //FILTER for STEREOBM

    int ndisparities = intsld1*intsld3;
    int SADWindowSize = intsld2;
    Ptr<StereoBM> sbm = StereoBM::create( ndisparities, SADWindowSize );

    //-- 3. Calculate the disparity image
    sbm->compute( imgLeft, imgRight, imgDisparity16S );

    //-- Check its extreme values
    double minVal; double maxVal;
    minMaxLoc( imgDisparity16S, &minVal, &maxVal );

    qDebug() << "min: " << minVal << " / max: " << maxVal;

    //-- 4. Display it as a CV_8UC1 image
    imgDisparity16S.convertTo( imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));

    namedWindow( "windowDisparity", WINDOW_NORMAL );
    imshow( "windowDisparity", imgDisparity8U );

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter paint;
    paint.begin(this);
    if(showimg){
        iplimg = cvQueryFrame(capture);
        qtimage = IplImage2QImage(iplimg);
        paint.drawImage(0,0,*qtimage);
    }
    paint.end();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt:: Key_O:
        {
            break;
        }

        case Qt::Key_P:
        {
            showimg = true;
            break;
        }

        case Qt::Key_W:
        {
            break;
        }

        case Qt::Key_B:
        {
            break;
        }

        case Qt::Key_Q:
        {
            bla = false;
            this->close();
            break;
        }

        case Qt::Key_S:
        {
            stereoma();
            break;
        }

        case Qt::Key_D:
        {
        qDebug() << "d";
            yomi = false;
            stereoma();
            break;
        }
    }
}
