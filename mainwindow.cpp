//mainwindow.cpp
//date : 2016/06/01
//auther : Shunsuke Izumi
//discription : TopWindow, organize each widget

#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>

//TopWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    makeMenu();

    //Viewer
    viewer = new View;
    viewer->p_main = this;
    this->setCentralWidget(viewer);

    //Controls
    conpane = new control;
    dock_conpane = new QDockWidget;
    dock_conpane->setWidget(conpane);
    this->addDockWidget(Qt::RightDockWidgetArea,dock_conpane);

    //
    str_lastdir = ".";

    QObject::connect(conpane->spn01,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(conpane->spn02,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(conpane->spn03,SIGNAL(valueChanged(int)),this,SLOT(slid()));

    QObject::connect(conpane->spnZoom,SIGNAL(valueChanged(int)),this,SLOT(slot_zoom()));
}

//To loading image, main stream
void MainWindow::mainfunc()
{
    QStringList str_list = opendlg();
    if(!str_list.isEmpty()){
        viewer->loadimg(str_list);
    }else{
        QMessageBox xbox;
        xbox.setText("Select 2 images");
        xbox.exec();
    }
}

//Open image dialog, only allow two image select at the time. if its one image, open dlg for second image.
QStringList MainWindow::opendlg(){
    QStringList filenam;
    filenam = QFileDialog::getOpenFileNames(this, tr("Open 2 Image, you can select two at the same time"), str_lastdir,tr("Image file (*.jpg *.jpeg *.png *bmp)"));

    if(filenam.isEmpty()){
        return QStringList();
    }else if(filenam.size() == 1){
        str_lastdir = filenam.first();
        QString strtemp;
        strtemp = opendlg_2times();
        if (strtemp.isEmpty()){
            QPixmap tmppix(filenam.first());
            viewer->l_screen->setPixmap(tmppix);
            return QStringList();
        }else{
            filenam.append(strtemp);
        }
    }

    QString str1 = filenam.at(0);
    QString str2 = filenam.at(1);
    str_lastdir = str1;

    QStringList resultlist;
    resultlist.append(str1);
    resultlist.append(str2);

    return resultlist;
}

QString MainWindow::opendlg_2times(){
    QString strtmp;
    strtmp = QFileDialog::getOpenFileName(this, tr("Open Image"), str_lastdir,tr("Image file (*.jpg *.jpeg *.png *bmp)"));
    if(strtmp.isEmpty()){
        return QString();
    }else{
        return strtmp;
    }
}

//update viewer's value
void MainWindow::slid()
{
    if (!viewer->imageloaded)
        return;

    viewer->intsld1 = conpane->spn01->value();
    viewer->intsld2 = conpane->spn02->value();
    viewer->intsld3 = conpane->spn03->value();

    viewer->stereobm();

    viewer->update();
}

//Menubar setup
void MainWindow::makeMenu()
{
    QString title1 = QString::fromLocal8Bit("File");

    //親メニュー
    QMenu* menu1 = new QMenu(title1, this);

    act_openimage = new QAction(tr("&Open Image"), this);
    QObject::connect(act_openimage,SIGNAL(triggered()),this, SLOT(mainfunc()));

    act_quit = new QAction(tr("&Quit"), this);
    QObject::connect(act_quit,SIGNAL(triggered()),this, SLOT(slot_quitApp()));

    menu1->addAction(act_openimage);
    menu1->addSeparator();
    menu1->addAction(act_quit);

    menubar = this->menuBar();
    menubar->addMenu(menu1);
}

//Fullscreen / show normal control
void MainWindow::slot_fulls()
{
    if(this->isFullScreen()){
        this->showNormal();
        menubar->show();
    }else{
        this->showFullScreen();
        menubar->hide();
    }
}

/////////////////////EVENT///////////////////

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt:: Key_O:
        {
        mainfunc();
        break;
        }

    case Qt::Key_Space:
        {
            if(dock_conpane->isVisible()){
                dock_conpane->hide();
            }else{
                dock_conpane->show();
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();

    pressed_xpos = event->x();
    pressed_ypos = event->y();

    switch(event->buttons())
    {
    case Qt::LeftButton:
        if(!this->isFullScreen()){
            flag_left_down = true;
        }
        break;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    pressed_xpos = 0;pressed_ypos = 0;current_xpos = 0;current_ypos = 0;
    if(event->button() == Qt::LeftButton){
            flag_left_down = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    current_xpos = event->x();
    current_ypos = event->y();

    if(flag_left_down){
        QPoint xy_pressed(pressed_xpos, pressed_ypos);
        QPoint diff = event->pos() - xy_pressed;
        this->move(this->pos() + diff);
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        this->slot_fulls();
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu *menuRight  = new QMenu(this);\
    menuRight->addAction(act_openimage);
    menuRight->addAction(act_quit);

    QPoint menuLocation = event->globalPos();
    menuRight->exec(QPoint(menuLocation.x() ,menuLocation.y()));
}

void MainWindow::slot_quitApp()
{
    QApplication::quit();
}

void MainWindow::slot_zoom()
{
    if(viewer->pix.isNull()){ return;}

    viewer->pixmap_scale(conpane->spnZoom->value());
}
