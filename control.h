#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtGui>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

class control : public QWidget
{
    Q_OBJECT
public:
    explicit control(QWidget *parent = 0);

    QVBoxLayout *lay_main_v;
    QSpinBox *spn01;
    QSpinBox *spn02;
    QSpinBox *spn03;

    QLabel *l01;
    QLabel *l02;
    QLabel *l03;

    QSlider *sl01;
    QSlider *sl02;
    QSlider *sl03;

    void setup_slot();

    QLabel   *lzoom;
    QSpinBox *spnZoom;
    QPushButton *b_zoomreset;

signals:

public slots:
    void slot_zoomreset();
};

#endif // CONTROL_H
