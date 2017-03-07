#include "cqtopencvviewergl.h"

#include <QOpenGLFunctions>
#include <opencv2/opencv.hpp>

CQtOpenCVViewerGl::CQtOpenCVViewerGl(QWidget *parent) :
QOpenGLWidget(parent)
{
    mBgColor = QColor::fromRgb(150, 150, 150);
    mStartPoint=QPoint(0,0);
    mStopPoint=QPoint(0,0);
    setMouseTracking(true);
    mMousePress=false;
}

CQtOpenCVViewerGl::~CQtOpenCVViewerGl()
{
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    doneCurrent();
}

void CQtOpenCVViewerGl::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();

    float r = ((float)mBgColor.darker().red())/255.0f;
    float g = ((float)mBgColor.darker().green())/255.0f;
    float b = ((float)mBgColor.darker().blue())/255.0f;
    glClearColor(r,g,b,1.0f);
}

void CQtOpenCVViewerGl::resizeGL(int width, int height)
{
    makeCurrent();
    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, -height, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    recalculatePosition();

    emit imageSizeChanged(mRenderWidth, mRenderHeight);

    updateScene();
}

void CQtOpenCVViewerGl::updateScene()
{
    if (this->isVisible()) update();
}

void CQtOpenCVViewerGl::paintGL()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderImage();
}

void CQtOpenCVViewerGl::renderImage()
{
    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    if (!mRenderQtImg.isNull())
    {
        glLoadIdentity();

        glPushMatrix();
        {
            if (mResizedImg.width() <= 0)
            {
                if (mRenderWidth == mRenderQtImg.width() && mRenderHeight == mRenderQtImg.height())
                    mResizedImg = mRenderQtImg;
                else
                    mResizedImg = mRenderQtImg.scaled(QSize(mRenderWidth, mRenderHeight),
                                                      Qt::IgnoreAspectRatio,
                                                      Qt::SmoothTransformation);
            }

            // ---> Centering image in draw area

            glRasterPos2i(mRenderPosX, mRenderPosY);

            glPixelZoom(1, -1);

            glDrawPixels(mResizedImg.width(), mResizedImg.height(), GL_RGBA, GL_UNSIGNED_BYTE, mResizedImg.bits());
        }
        glPopMatrix();

        // end
        glFlush();
    }
    if(mMousePress)
    {
      glRecti(mStartPoint.x(),mStartPoint.y(),mStopPoint.x(),mStopPoint.y());
    }

}

void CQtOpenCVViewerGl::mousePressEvent(QMouseEvent *event)
{
    mStartPoint=event->pos();
    mStopPoint=event->pos();
    mMousePress=true;
    QOpenGLWidget::mousePressEvent(event);
}

void CQtOpenCVViewerGl::mouseReleaseEvent(QMouseEvent *event)
{
    mMousePress=false;
    QOpenGLWidget::mouseReleaseEvent(event);
}

void CQtOpenCVViewerGl::mouseMoveEvent(QMouseEvent *event)
{
    if(mMousePress)
    {
        mStopPoint=event->pos();
        //updateScene();
    }
   // qDebug()<<"POS: "<<event->pos();
    QOpenGLWidget::mouseMoveEvent(event);
}

void CQtOpenCVViewerGl::recalculatePosition()
{
    mImgRatio = (float)mOrigImage.cols/(float)mOrigImage.rows;

    mRenderWidth = this->size().width();
    mRenderHeight = floor(mRenderWidth / mImgRatio);

    if (mRenderHeight > this->size().height())
    {
        mRenderHeight = this->size().height();
        mRenderWidth = floor(mRenderHeight * mImgRatio);
    }

    mRenderPosX = floor((this->size().width() - mRenderWidth) / 2);
    mRenderPosY = -floor((this->size().height() - mRenderHeight) / 2);

    mResizedImg = QImage();
}

bool CQtOpenCVViewerGl::showImage(const cv::Mat& image)
{
    if (image.channels() == 3)
        cvtColor(image, mOrigImage, CV_BGR2RGBA);
    else if (mOrigImage.channels() == 1)
        cvtColor(image, mOrigImage, CV_GRAY2RGBA);
    else return false;

    mRenderQtImg = QImage((const unsigned char*)(mOrigImage.data),
                          mOrigImage.cols, mOrigImage.rows,
                          mOrigImage.step1(), QImage::Format_RGB32);

    recalculatePosition();

    updateScene();

    return true;
}
