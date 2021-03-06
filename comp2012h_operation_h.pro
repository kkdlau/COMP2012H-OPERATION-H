QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network bluetooth multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# For promoted widgets
INCLUDEPATH += GameScene/

SOURCES += \
    GameCharacter/character.cpp \
    GameCharacter/character_controller.cpp \
    GameCharacter/charactermanager.cpp \
    GameCharacter/enemy.cpp \
    NewWeapon/bullet.cpp \
    GameScene/overlay.cpp \
    GameScene/camera.cpp \
    GameScene/gridinfo.cpp \
    NewWeapon/meleeweapon.cpp \
    NewWeapon/rangedweapon.cpp \
    NewWeapon/weapon.cpp \
    NewWeapon/weaponmanager.cpp \
    UI/healthbar.cpp \
    Pathing/astar.cpp \
    UI/itemframe.cpp \
    GameScene/gamemapcanvas.cpp \
    GameScene/map.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp \
    optionpage.cpp

HEADERS += \
    GameCharacter/character.h \
    GameCharacter/charactermanager.h \
    GameCharacter/enemy.h \
    GameScene/overlay.h \
    GameScene/camera.h \
    GameScene/gridinfo.h \
    NewWeapon/bullet.h \
    NewWeapon/meleeweapon.h \
    NewWeapon/rangedweapon.h \
    NewWeapon/weapon.h \
    NewWeapon/weaponmanager.h \
    UI/healthbar.h \
    Pathing/astar.h \
    UI/itemframe.h \
    GameScene/gamemapcanvas.h \
    GameScene/map.h \
    mainwindow.h \
    mapviewpage.h \
    optionpage.h

FORMS += \
    mainwindow.ui \
    mapviewpage.ui \
    optionpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
