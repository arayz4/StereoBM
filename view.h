#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QtGui>
#include <QFileDialog>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

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
    void loadimg(QStringList);
    void stereobm();

    bool imageloaded;

    QImage* IplImage2QImage(const IplImage *iplImg);

    QImage qtimage;

    QLabel *l_screen;
    QHBoxLayout *lay_screen;
    QPixmap pix;

    //Disparity
    Mat imgLeft;
    Mat imgRight;
    Mat imgDisparity16S;
    Mat imgDisparity8U;

    //parameter
    int intsld1;
    int intsld2;
    int intsld3;

    //Image size check
    QPixmap pixmap_sizemodify(QPixmap);
    void pixmap_scale(int zoom);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // VIEW_H
