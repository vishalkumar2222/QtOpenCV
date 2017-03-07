#include "customvideoclass.h"

CustomVideoClass::CustomVideoClass(QWidget *parent)
    :QLabel(parent)
{
    mStartPoint=QPoint(0,0);
    mStopPoint=QPoint(0,0);
    setMouseTracking(true);
    mMousePress=false;
}

void CustomVideoClass::setPixmap(const QPixmap &image)
{
    mImage=image;
    update();
}

void CustomVideoClass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawPixmap(this->rect(),mImage);
    if(mMousePress)
    {
      painter.drawRect(QRect(mStartPoint,mStopPoint));
    }

    QLabel::paintEvent(event);
}

void CustomVideoClass::mousePressEvent(QMouseEvent *event)
{
    mStartPoint=event->pos();
    mStopPoint=event->pos();
    mMousePress=true;
}

void CustomVideoClass::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    mMousePress=false;
}

void CustomVideoClass::mouseMoveEvent(QMouseEvent *event)
{
    if(mMousePress)
    {
        mStopPoint=event->pos();
        update();
    }
}
