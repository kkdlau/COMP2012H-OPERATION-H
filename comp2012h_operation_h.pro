QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# For promoted widgets
INCLUDEPATH += GameMapCanvas/

SOURCES += \
    KeyBoardManager/combo.cpp \
    KeyBoardManager/keyboardmanager.cpp \
    GameMapCanvas/gamemapcanvas.cpp \
    GameMapCanvas/map.cpp \
    Weapons/meleeweapon.cpp \
    Weapons/weapon.cpp \
    CharacterManager/character_manager.cpp \
    Parser/FileParser.cpp \
    Weapons/shield.cpp \
    character.cpp \
    main.cpp \
    mainwindow.cpp \
    mapviewpage.cpp \

HEADERS += \
    KeyBoardManager/combo.h \
    KeyBoardManager/keyboardmanager.h \
    KeyBoardManager/KeyState.h \
    Weapons/meleeweapon.h \
    GameMapCanvas/gamemapcanvas.h \
    GameMapCanvas/map.h \
    Weapons/weapon.h \
    CharacterManager/character_manager.h \
    Parser/FileParser.h \
    Weapons/shield.h \
    character.h \
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
