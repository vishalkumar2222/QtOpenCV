#-------------------------------------------------
#
# Project created by QtCreator 2017-01-02T10:39:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    opencv_thread.cpp \
    customvideoclass.cpp \
    cqtopencvviewergl.cpp

HEADERS  += mainwindow.h \
    opencv_thread.h \
    customvideoclass.h \
    cqtopencvviewergl.h

FORMS    += mainwindow.ui

INCLUDEPATH +=C:/opencv/Release/install/include


LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_features2d2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_flann2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_gpu2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_highgui2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_imgproc2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_legacy2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_ml2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_nonfree2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_objdetect2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_ocl2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_photo2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_stitching2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_superres2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_ts2413.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_video2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_videostab2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_calib3d2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_contrib2413.dll.a"
LIBS +="C:\opencv\Release\install\x86\mingw\lib\libopencv_core2413.dll.a"


DEPENDPATH += C:/opencv/Release/install/x86/mingw/bin

RESOURCES += \
    icon.qrc
