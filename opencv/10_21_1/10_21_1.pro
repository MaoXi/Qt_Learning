#-------------------------------------------------
#
# Project created by QtCreator 2018-10-21T16:17:43
#
#-------------------------------------------------

QT       += core gui
INCLUDEPATH += D:/program/OpenCV/opencv/build/include/ \  #添加函数头文件目录，根据自己install文件夹目录进行路径修改，下面也一样
               D:/program/OpenCV/opencv/build/include/opencv\
               D:/program\OpenCV\opencv\build\include\opencv2

LIBS += D:\program\OpenCV\opencv\build\x64\vc14\lib\opencv_world320.lib\
        D:\program\OpenCV\opencv\build\x64\vc14\lib\opencv_world320d.lib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 10_21_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../program/OpenCV/opencv/build/x64/vc14/lib/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../program/OpenCV/opencv/build/x64/vc14/lib/ -lopencv_world320d
else:unix: LIBS += -L$$PWD/../../program/OpenCV/opencv/build/x64/vc14/lib/ -lopencv_world320

INCLUDEPATH += $$PWD/../../program/OpenCV/opencv/build/x64/vc14
DEPENDPATH += $$PWD/../../program/OpenCV/opencv/build/x64/vc14

DISTFILES +=

RESOURCES += \
    pic.qrc
