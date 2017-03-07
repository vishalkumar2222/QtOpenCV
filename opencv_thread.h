#ifndef OPENCV_THREAD_H
#define OPENCV_THREAD_H

#include<QThread>
#include<QFile>
#include<QTimer>
#include<QImage>
#include "opencv2/highgui/highgui.hpp"
#include<QDebug>
#include<QDateTime>
class OpenCV_Thread : public QThread
{
    Q_OBJECT
public:
    OpenCV_Thread(QObject *parent=0);

    bool m_bClosed;
    int m_iRecording;
    bool m_bSnap;
    int m_CameraNumber;
    QSize m_Size;
    QString m_VideoDir;
    QString m_ImageDir;
signals:
    void newImage(QImage image);
    void recordingStarted();
    void recordingFinished();
    void Connected(int status);
    void snapResult(bool status);
    void newImageMat(cv::Mat mat);
protected:
    void run()Q_DECL_OVERRIDE;
private:
    cv::VideoCapture *m_Vidcapture;
    cv::VideoWriter *m_VidWritter;
};

#endif // OPENCV_THREAD_H
