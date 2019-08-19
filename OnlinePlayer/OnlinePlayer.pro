#-------------------------------------------------
#
# Project created by QtCreator 2019-08-15T16:52:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OnlinePlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        playerwidget.cpp

HEADERS += \
        playerwidget.h

FORMS += \
        playerwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

msvc{
    QMAKE_CFLAGS += -source-charset:utf-8
    QMAKE_CXXFLAGS += -source-charset:utf-8
}

# 附加包含路径
INCLUDEPATH += \
        $$PWD/../QtAV/src/QtAV \
        $$PWD/../QtAV\src \
        $$PWD/../QtAV\widgets \
        $$PWD/../QtAV\widgets\QtAVWidgets \
        $$PWD/../QtUtils\uibase

# ***********************************************************
# Win平台下配置
# ***********************************************************
win32 {
    include($$PWD/../QtUtils/uibase/uibase.pri)
    contains(QT_ARCH, x86_64) {
        message("x64")
        # 输出目录
        CONFIG(debug, debug|release) {
            DESTDIR = $$PWD/../output/win64/debug
        } else {
            DESTDIR = $$PWD/../output/win64/release
        }
    } else {
        message("x86")        
        CONFIG(debug, debug|release) {
            # 输出目录
            DESTDIR = $$PWD/../output/win32/debug
            # 依赖模块
            LIBS += \
                -L$$PWD/../third_party/QtAV/win32/debug/lib -lQtAVd1 \
                -L$$PWD/../third_party/QtAV/win32/debug/lib -lQtAVWidgetsd1

            # 设置依赖库目录
            WIN_QTAV_SRC = $$PWD/../third_party/QtAV/win32/debug/bin/*.dll
            WIN_DST = $$PWD/../output/win32/debug

        } else {
            # 输出目录
            DESTDIR = $$PWD/../output/win32/release
            # 依赖模块
            LIBS += \
                -L$$PWD/../third_party/QtAV/win32/release/lib -lQtAV1 \
                -L$$PWD/../third_party/QtAV/win32/release/lib -lQtAVWidgets1

            # 设置依赖库目录
            WIN_QTAV_SRC = $$PWD/../third_party/QtAV/win32/release/bin/*.dll
            WIN_DST = $$PWD/../output/win32/release
        }

        # 复制依赖库
        WIN_FFMPEG_SRC = $$PWD/../third_party/ffmpeg/win32/bin/*.dll

        WIN_QTAV_SRC ~= s,/,\\,g
        WIN_FFMPEG_SRC ~= s,/,\\,g
        WIN_DST ~= s,/,\\,g

        QMAKE_POST_LINK += $$quote($$QMAKE_COPY $$WIN_QTAV_SRC $$WIN_DST$$escape_expand(\n\t))
        QMAKE_POST_LINK += $$quote($$QMAKE_COPY $$WIN_FFMPEG_SRC $$WIN_DST$$escape_expand(\n\t))
    }    
}

# ***********************************************************
# Mac平台下配置
# ***********************************************************
macos {
    # 输出目录
    CONFIG(debug, debug|release) {
        DESTDIR = $$PWD/../output/mac64/debug
    } else {
        DESTDIR = $$PWD/../output/mac64/release
    }
}

# ***********************************************************
# Linux平台下配置
# ***********************************************************
linux {
    # 输出目录
    CONFIG(debug, debug|release) {
        DESTDIR = $$PWD/../output/linux64/debug
    } else {
        DESTDIR = $$PWD/../output/linux64/release
    }
}

RESOURCES += \
    res.qrc
