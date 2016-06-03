//control.cpp
//date : 2016/06/01
//auther : Shunsuke Izumi
//discription : control panel to change values

#include "control.h"

control::control(QWidget *parent) : QWidget(parent)
{
    int v01_def,v01_step,v01_min,v01_max;
    int v02_def,v02_step,v02_min,v02_max;
    int v03_def,v03_step,v03_min,v03_max;

    //v01
    v01_def  = 16;
    v01_step = 16;
    v01_min  = 0;
    v01_max  = 160;

    //v02
    v02_def  = 21;
    v02_step = 2;
    v02_min  = 5;
    v02_max  = 255;

    //v03
    v03_def  = 5;
    v03_step = 1;
    v03_min  = 1;
    v03_max  = 25;

    //widget
    lay_main_v = new QVBoxLayout;
    spn01      = new QSpinBox;
    spn02      = new QSpinBox;
    spn03      = new QSpinBox;

    l01        = new QLabel("Value 1");
    l02        = new QLabel("Value 2");
    l03        = new QLabel("Value 3");

    sl01       = new QSlider(Qt::Horizontal);
    sl02       = new QSlider(Qt::Horizontal);
    sl03       = new QSlider(Qt::Horizontal);

    lzoom      = new QLabel("Zoom in/out");
    spnZoom    = new QSpinBox;
    b_zoomreset= new QPushButton("Zoom reset");

    l_desc     = new QLabel;

    //setup control value
    spn01->setValue(v01_def);
    spn01->setSingleStep(v01_step);
    spn01->setRange(v01_min,v01_max);

    spn02->setValue(v02_def);
    spn02->setSingleStep(v02_step);
    spn02->setRange(v02_min,v02_max);

    spn03->setValue(v03_def);
    spn03->setSingleStep(v03_step);
    spn03->setRange(v03_min,v03_max);

    sl01->setValue(v01_def);
    sl01->setSingleStep(v01_step);
    sl01->setRange(v01_min,v01_max);

    sl02->setValue(v02_def);
    sl02->setSingleStep(v02_step);
    sl02->setRange(v02_min,v02_max);

    sl03->setValue(v03_def);
    sl03->setSingleStep(v03_step);
    sl03->setRange(v03_min,v03_max);

    spnZoom->setRange(10,150);
    spnZoom->setValue(100);
    spnZoom->setSingleStep(10);

    //Layout
    this->setLayout(lay_main_v);
    lay_main_v->addWidget(l01);
    lay_main_v->addWidget(spn01);
    //lay_main_v->addWidget(sl01);
    lay_main_v->addSpacing(10);
    lay_main_v->addWidget(l02);
    lay_main_v->addWidget(spn02);
    //lay_main_v->addWidget(sl02);
    lay_main_v->addSpacing(10);
    lay_main_v->addWidget(l03);
    lay_main_v->addWidget(spn03);
    //lay_main_v->addWidget(sl03);
    lay_main_v->addSpacing(20);
    lay_main_v->addWidget(lzoom);
    lay_main_v->addWidget(spnZoom);
    lay_main_v->addWidget(b_zoomreset);
    lay_main_v->addStretch();

    //Slot connection
    setup_slot();

    l_desc->setText("Open image :\n Menubar\n Right click\n Short cut [O]\n\n"
                    "Fullscreen :\n Double click\n\nShow/hide panel :\n [Space]");
    lay_main_v->addWidget(l_desc);
}

void control::slot_zoomreset()
{
    spnZoom->setValue(100);
}

void control::setup_slot()
{
    QObject::connect(spn01,SIGNAL(valueChanged(int)),sl01,SLOT(setValue(int)));
    QObject::connect(sl01,SIGNAL(valueChanged(int)),spn01,SLOT(setValue(int)));
    QObject::connect(spn02,SIGNAL(valueChanged(int)),sl02,SLOT(setValue(int)));
    QObject::connect(sl02,SIGNAL(valueChanged(int)),spn02,SLOT(setValue(int)));
    QObject::connect(spn03,SIGNAL(valueChanged(int)),sl03,SLOT(setValue(int)));
    QObject::connect(sl03,SIGNAL(valueChanged(int)),spn03,SLOT(setValue(int)));

    QObject::connect(b_zoomreset,SIGNAL(pressed()),this,SLOT(slot_zoomreset()));
}
