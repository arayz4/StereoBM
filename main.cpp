//OpenCV 3.1.0
//Qt 5.6

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString g_appPath = QCoreApplication::applicationDirPath();

    //m_pMyWidget->setStyleSheet("background-color:black;");

    QPixmap pixsplash;//(g_appPath + "/Splash.png");
    pixsplash.load(g_appPath + "/Splash.png");
    QSplashScreen splash(pixsplash);
    splash.show();
    a.processEvents();
    splash.showMessage("Version 1.0.0",Qt::AlignRight | Qt::AlignBottom, Qt::white);

    MainWindow w;
    w.setWindowTitle("StereoBM version 1.0.0");
    w.setGeometry(300,300,400,300);
    w.show();

    QThread::msleep(850);//本来不要

    splash.finish(&w);

    return a.exec();
}
