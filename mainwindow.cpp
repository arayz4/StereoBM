#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Viewer
    viewer = new View;
    viewer->p_main = this;
    this->setCentralWidget(viewer);

    //Controls
    conpane = new control;
    dock_conpane = new QDockWidget;
    dock_conpane->setWidget(conpane);
    this->addDockWidget(Qt::LeftDockWidgetArea,dock_conpane);

    QObject::connect(conpane->spn01,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(conpane->spn02,SIGNAL(valueChanged(int)),this,SLOT(slid()));
    QObject::connect(conpane->spn03,SIGNAL(valueChanged(int)),this,SLOT(slid()));

}

void MainWindow::slid()
{
    viewer->intsld1 = conpane->spn01->value();
    viewer->intsld2 = conpane->spn02->value();
    viewer->intsld3 = conpane->spn03->value();

    viewer->stereobm();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt:: Key_O:
        {
            qDebug() << "O";
            break;
        }

        case Qt::Key_P:
        {
            qDebug() << "P";
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
            this->close();
            break;
        }

        case Qt::Key_S:
        {
            viewer->stereobm();
            break;
        }

        case Qt::Key_D:
        {
            viewer->yomi = false;
            viewer->stereobm();
            break;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    switch(event->buttons())
    {
    case Qt::LeftButton:
        this->setFocus();
        break;
    }
}
