QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# For promoted widgets
INCLUDEPATH += GameScene/

SOURCES += \
    ../../Program/comp2012h_operation_h/GameScene/overlay.cpp \
    GameScene/camera.cpp \
    GameScene/gridinfo.cpp \
    FileParser/fileparser.cpp \
    KeyBoardManager/combo.cpp \
    KeyBoardManager/keyboardmanager.cpp \
    Network/client.cpp \
    Network/server.cpp \
    NewWeapon/meleeweapon.cpp \
    NewWeapon/rangedweapon.cpp \
    NewWeapon/weapon.cpp \
    NewWeapon/weaponmanager.cpp \
    UI/healthbar.cpp \
    Pathing/astar.cpp \
    UI/itemframe.cpp \
    Weapons/bullet.cpp \
    GameScene/gamemapcanvas.cpp \
    GameScene/map.cpp \
    character.cpp \
    charactermanager.cpp \
    clientpage.cpp \
    enemy.cpp \
    hostpage.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp \
    Network/udp.cpp \
    networkpage.cpp

HEADERS += \
    ../../Program/comp2012h_operation_h/GameScene/overlay.h \
    GameScene/camera.h \
    GameScene/gridinfo.h \
    FileParser/fileparser.h \
    KeyBoardManager/combo.h \
    KeyBoardManager/keyboardmanager.h \
    KeyBoardManager/KeyState.h \
    Network/client.h \
    Network/server.h \
    NewWeapon/meleeweapon.h \
    NewWeapon/rangedweapon.h \
    NewWeapon/weapon.h \
    NewWeapon/weaponmanager.h \
    UI/healthbar.h \
    Pathing/astar.h \
    UI/itemframe.h \
    Weapons/bullet.h \
    GameScene/gamemapcanvas.h \
    GameScene/map.h \
    character.h \
    charactermanager.h \
    clientpage.h \
    enemy.h \
    hostpage.h \
    mainwindow.h \
    mapviewpage.h \
    Network/udp.h \
    networkpage.h

FORMS += \
    clientpage.ui \
    hostpage.ui \
    mainwindow.ui \
    mapviewpage.ui \
    networkpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
