#ifndef CUSTOMVIDEOCLASS_H
#define CUSTOMVIDEOCLASS_H

#include<QLabel>
#include<QPaintEvent>
#include<QPainter>
#include<QMouseEvent>
#include<QDebug>
class CustomVideoClass : public QLabel
{
public:
    CustomVideoClass(QWidget *parent=0);
    void setPixmap(const QPixmap &image);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint mStartPoint,mStopPoint;
    bool mMousePress;
    QPixmap mImage;
};

#endif // CUSTOMVIDEOCLASS_H
