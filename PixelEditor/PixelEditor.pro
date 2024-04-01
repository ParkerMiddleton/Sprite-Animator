QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PRECOMPILED_HEADER = qt_std_pch.h

SOURCES += \
    createnewspritedialog.cpp \
    frameicon.cpp \
    layericon.cpp \
    editor.cpp \
    layerspanel.cpp \
    main.cpp \
    mainwindow.cpp \
    previewpanel.cpp \
    spritemodel.cpp \
    timelinepanel.cpp \
    viewport.cpp

HEADERS += \
    createnewspritedialog.h \
    frameicon.h \
    layericon.h \
    editor.h \
    layerspanel.h \
    mainwindow.h \
    previewpanel.h \
    spritemodel.h \
    timelinepanel.h \
    viewport.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
