#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT
#include <QMainWindow>
#include <QtGui>
#include <QImage>

#include <QDockWidget>

#include "view.h"
#include "control.h"

//GUI
#include <QSpinBox>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    //View
    View *viewer;

    //Controls
    control *conpane;
    QDockWidget *dock_conpane;

public slots:
    void slid();

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
