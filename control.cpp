#include "control.h"

control::control(QWidget *parent) : QWidget(parent)
{
    lay_main_v = new QVBoxLayout;
    spn01      = new QSpinBox;
    spn02      = new QSpinBox;
    spn03      = new QSpinBox;

    spn01->setValue(16);
    spn01->setSingleStep(16);
    spn01->setRange(0,160);

    spn02->setValue(21);
    spn02->setRange(5,255);
    spn02->setSingleStep(2);

    spn03->setValue(5);
    spn03->setRange(1,25);
    spn03->setSingleStep(1);

    this->setLayout(lay_main_v);
    lay_main_v->addWidget(spn01);
    lay_main_v->addWidget(spn02);
    lay_main_v->addWidget(spn03);
    lay_main_v->addStretch();
}
