#ifndef CQTOPENCVVIEWERGL_H
#define CQTOPENCVVIEWERGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <opencv2/core/core.hpp>
#include <QMouseEvent>
#include<QDebug>
class CQtOpenCVViewerGl : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
    Q_OBJECT
public:
    explicit CQtOpenCVViewerGl(QWidget *parent = 0);
    ~CQtOpenCVViewerGl();
signals:
    void    imageSizeChanged( int outW, int outH );

public slots:
    bool    showImage(const cv::Mat& image);

protected:
    void 	initializeGL();
    void 	paintGL();
    void 	resizeGL(int width, int height);

    void     updateScene();
    void     renderImage();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

    QImage   mRenderQtImg;
    QImage   mResizedImg;
    cv::Mat  mOrigImage;
    QColor  mBgColor;
    float  mImgRatio;

    int mRenderWidth;
    int mRenderHeight;
    int mRenderPosX;
    int mRenderPosY;

    void recalculatePosition();

    QPoint mStartPoint,mStopPoint;
    bool mMousePress;
};

#endif // CQTOPENCVVIEWERGL_H
