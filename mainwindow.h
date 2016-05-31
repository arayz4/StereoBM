#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT
#include <QMainWindow>
#include <QtGui>
#include <QImage>

#include <QDockWidget>

#include <QMenuBar>

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

    QStringList imagelist;

    //View
    View *viewer;

    //Controls
    control *conpane;
    QDockWidget *dock_conpane;

    QStringList opendlg();

    //Window
    int pressed_xpos;
    int pressed_ypos;
    int current_xpos;
    int current_ypos;
    bool flag_left_down;

    void makeMenu();
    QMenuBar *menubar;
    QAction *act_openimage;
    QAction *act_quit;

public slots:
    void slid();
    void mainfunc();
    void slot_quitApp();

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // MAINWINDOW_H
