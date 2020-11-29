QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# For promoted widgets
INCLUDEPATH += GameMapCanvas/

SOURCES += \
    GameMapCanvas/gridinfo.cpp \
    FileParser/fileparser.cpp \
    KeyBoardManager/combo.cpp \
    KeyBoardManager/keyboardmanager.cpp \
    NewWeapon/meleeweapon.cpp \
    NewWeapon/rangedweapon.cpp \
    NewWeapon/weapon.cpp \
    Weapons/bullet.cpp \
    GameMapCanvas/gamemapcanvas.cpp \
    GameMapCanvas/map.cpp \
    character.cpp \
    charactermanager.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp \

HEADERS += \
    GameMapCanvas/gridinfo.h \
    FileParser/fileparser.h \
    KeyBoardManager/combo.h \
    KeyBoardManager/keyboardmanager.h \
    KeyBoardManager/KeyState.h \
    NewWeapon/meleeweapon.h \
    NewWeapon/rangedweapon.h \
    NewWeapon/weapon.h \
    Weapons/bullet.h \
    GameMapCanvas/gamemapcanvas.h \
    GameMapCanvas/map.h \
    character.h \
    charactermanager.h \
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
    assets.qrc
