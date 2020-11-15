QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../Program/comp2012h_operation_h/KeyBoardManager/combo.cpp \
    ../../Program/comp2012h_operation_h/KeyBoardManager/keyboardmanager.cpp \
    ../../Program/comp2012h_operation_h/widgets/gamemapcanvas.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp

HEADERS += \
    ../../Program/comp2012h_operation_h/KeyBoardManager/combo.h \
    ../../Program/comp2012h_operation_h/KeyBoardManager/keyboardmanager.h \
     ../../Program/comp2012h_operation_h/KeyBoardManager/KeyState.h \
    ../../Program/comp2012h_operation_h/widgets/gamemapcanvas.h \
    mainwindow.h \
    mapviewpage.h

FORMS += \
    mainwindow.ui \
    mapviewpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../Program/comp2012h_operation_h/assets.qrc
