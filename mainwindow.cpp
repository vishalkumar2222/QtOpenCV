#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_bCloseRequested=false;
    m_bThreadRunning=false;
    m_bControlVisible=false;
    recordButton=new QPushButton(QIcon(":/images/record.png"),"",this);
    snapButton=new QPushButton(QIcon(":/images/snap.png"),"",this);
    recordButton->setFlat(true);
    snapButton->setFlat(true);
    recordButton->setIconSize(QSize(32,32));
    snapButton->setIconSize(QSize(32,32));
    connect(recordButton,SIGNAL(clicked(bool)),this,SLOT(startRecording()));
    connect(snapButton,SIGNAL(clicked(bool)),this,SLOT(takeSnap()));
    QTimer::singleShot(1000,this,SLOT(startCamera()));
    qRegisterMetaType<cv::Mat>("cv::Mat");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_bThreadRunning)
    {
        thread->m_bClosed=true;
        event->ignore();
        m_bCloseRequested=true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<insideHeader(event->pos());
    //QWidget::mouseMoveEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(event->size().width()<400||event->size().height()<300)
    {
        event->ignore();
    }
    else
    {
        QWidget::resizeEvent(event);
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    calculatePoint();
    QWidget::paintEvent(event);
}

void MainWindow::updateImage(QImage image)
{
    m_bThreadRunning=true;
    if(!image.isNull())
    {
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
    qApp->processEvents();
}

void MainWindow::threadDestroyed()
{
    m_bThreadRunning=false;
    if(m_bCloseRequested)
    {
        close();
    }
    else
    {
        recordButton->setEnabled(false);
        snapButton->setEnabled(false);
    }
}
void MainWindow::startCamera()
{
    thread=new OpenCV_Thread(this);
    connect(thread,SIGNAL(newImage(QImage)),this,SLOT(updateImage(QImage)));
    connect(thread,SIGNAL(newImageMat(cv::Mat)),ui->widget,SLOT(showImage(cv::Mat)));
    connect(thread,SIGNAL(recordingStarted()),this,SLOT(reacordingStarted()));
    connect(thread,SIGNAL(recordingFinished()),this,SLOT(recordingFinished()));
    connect(thread,SIGNAL(Connected(int)),this,SLOT(connectionStatus(int)));
    connect(thread,SIGNAL(snapResult(bool)),this,SLOT(snapResult(bool)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(thread,SIGNAL(finished()),this,SLOT(threadDestroyed()));
    thread->m_CameraNumber=0;
    thread->m_Size=QSize(ui->label->width()-10,ui->label->height()-10);
    thread->m_ImageDir="E:";
    thread->m_VideoDir="D:";
    thread->start();
    recordButton->setEnabled(true);
    snapButton->setEnabled(true);
}

void MainWindow::startRecording()
{
    if(thread->m_iRecording==0)
    {
        thread->m_iRecording=1;
    }
    else
    {
        thread->m_iRecording=3;
    }
}

void MainWindow::takeSnap()
{
    thread->m_bSnap=true;
}

void MainWindow::reacordingStarted()
{
    recordButton->setIcon(QIcon(":/images/stop.png"));
}

void MainWindow::recordingFinished()
{
    recordButton->setIcon(QIcon(":/images/record.png"));
}

void MainWindow::snapResult(bool status)
{
    if(status)
    {
        ui->statusBar->showMessage("Success",2000);
    }
    else
    {
        ui->statusBar->showMessage("Failed",2000);
    }
}
void MainWindow::connectionStatus(int status)
{
    switch (status) {
    case 0:
        ui->statusBar->showMessage("Unable to start Camera",-1);
        break;
    case 1:
        ui->statusBar->showMessage("Camera Disconnected",-1);
        break;
    }
}

void MainWindow::calculatePoint()
{
    QPoint centerPoint=ui->label->rect().center();
    int centerX=centerPoint.x();
    int yPosition=ui->label->height()-50;
    recordButton->setGeometry(centerX-50,yPosition,50,50);
    snapButton->setGeometry(centerX,yPosition,50,50);
}

bool MainWindow::insideHeader(QPoint point)
{
    return ui->label->rect().contains(point,true);
}
