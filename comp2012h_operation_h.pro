QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# For promoted widgets
INCLUDEPATH += GameMapCanvas/

SOURCES += \
    $$PWD/KeyBoardManager/combo.cpp \
    $$PWD/KeyBoardManager/keyboardmanager.cpp \
    $$PWD/Weapons/meleeweapon.cpp \
    $$PWD/Weapons/weapon.cpp \
    $$PWD/Weapons/handgun.cpp \
    $$PWD/Weapons/rangedweapon.cpp \
    $$PWD/GameMapCanvas/gamemapcanvas.cpp \
    $$PWD/GameMapCanvas/map.cpp \
    $$PWD/Weapons/shield.cpp \
    FileParser/fileparser.cpp \
    character.cpp \
    charactermanager.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp \

HEADERS += \
    $$PWD/KeyBoardManager/combo.h \
    $$PWD/KeyBoardManager/keyboardmanager.h \
    $$PWD/KeyBoardManager/KeyState.h \
    $$PWD/Weapons/meleeweapon.h \
    $$PWD/Weapons/weapon.h \
    $$PWD/Weapons/handgun.h \
    $$PWD/Weapons/rangedweapon.h \
    $$PWD/GameMapCanvas/gamemapcanvas.h \
    $$PWD/GameMapCanvas/map.h \
    $$PWD/Weapons/shield.h \
    FileParser/fileparser.h \
    character.h \
    charactermanager.h \
    mainwindow.h \
    mapviewpage.h \

FORMS += \
    mainwindow.ui \
    mapviewpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
