#include "opencv_thread.h"

OpenCV_Thread::OpenCV_Thread(QObject *parent)
    :QThread(parent)
{
    m_bClosed=false;
    m_iRecording=0;
    m_bSnap=false;
    m_CameraNumber=0;
}

void OpenCV_Thread::run()
{
    m_Vidcapture=new cv::VideoCapture(m_CameraNumber);
    //    m_Vidcapture=new cv::VideoCapture("http://192.168.0.164:8080/video?x.mjpeg");
    if(m_Vidcapture->isOpened())
    {
        while(1)
        {
            if(m_bClosed)
            {
                if(m_iRecording==2)
                {
                    m_VidWritter->release();
                }
                m_Vidcapture->release();
                break;
            }
            if(!m_Vidcapture->isOpened())
            {
                m_Vidcapture->release();
                emit Connected(1);
                break;
            }
            cv::Mat frame;

            bool bSuccess = m_Vidcapture->read(frame);

            if (!bSuccess)
            {
                break;
            }

            QImage target((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            target=target.scaled(m_Size,Qt::KeepAspectRatio);
            emit newImage(target);
            emit newImageMat(frame);
            switch (m_iRecording) {
            case 1:
            {
                double dWidth = m_Vidcapture->get(CV_CAP_PROP_FRAME_WIDTH);
                double dHeight = m_Vidcapture->get(CV_CAP_PROP_FRAME_HEIGHT);
                cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
                m_VidWritter=new cv::VideoWriter(QString(m_VideoDir+"/"+ QString(QDateTime::currentDateTime()
                                                         .toString("ddMMyyhhmmss")+".wmv")).toLocal8Bit().constData(),
                                                 CV_FOURCC('W','M','V','2'), 20, frameSize, true);
                if (m_VidWritter->isOpened())
                {
                    m_iRecording++;
                    m_VidWritter->write(frame);
                    emit recordingStarted();
                }
            }
                break;
            case 2:
                m_VidWritter->write(frame);
                break;
            case 3:
                m_VidWritter->release();
                emit recordingFinished();
            }
            if(m_bSnap)
            {
                cv::vector<int> compression_params;
                compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
                compression_params.push_back(98);
                bool bSuccess = cv::imwrite(QString(m_ImageDir+"/"+QString(QDateTime::currentDateTime().toString("ddMMyyhhmmss")+".jpg")).toLocal8Bit().constData(), frame, compression_params);
                emit snapResult(bSuccess);
                m_bSnap=false;
            }
            msleep(40);
        }
    }
    else
    {
        emit Connected(0);
    }
}
