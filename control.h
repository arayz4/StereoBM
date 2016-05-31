#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtGui>
#include <QSpinBox>

class control : public QWidget
{
    Q_OBJECT
public:
    explicit control(QWidget *parent = 0);

    QVBoxLayout *lay_main_v;
    QSpinBox *spn01;
    QSpinBox *spn02;
    QSpinBox *spn03;

signals:

public slots:
};

#endif // CONTROL_H
