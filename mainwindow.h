#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv_thread.h"
#include<QCloseEvent>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QPushButton>
#include<QMouseEvent>
#include<QHoverEvent>
#include"customvideoclass.h"
#include "opencv2/highgui/highgui.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    //void event(QEvent *event);
private slots:
    void updateImage(QImage image);
    void threadDestroyed();

    void startCamera();

    void startRecording();

    void takeSnap();

    void reacordingStarted();

    void recordingFinished();

    void snapResult(bool status);

    void connectionStatus(int status);

    void calculatePoint();

    bool insideHeader(QPoint point);



private:
    Ui::MainWindow *ui;
    OpenCV_Thread *thread;
    bool m_bCloseRequested;
    bool m_bThreadRunning;
    bool m_bControlVisible;
    QPoint m_Point;
    QPushButton *recordButton,*snapButton;
};

#endif // MAINWINDOW_H
