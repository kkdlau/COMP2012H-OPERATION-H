#ifndef MAPVIEWPAGE_H
#define MAPVIEWPAGE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "KeyBoardManager/keyboardmanager.h"
#include "NewWeapon/weaponmanager.h"
#include "charactermanager.h"
#include <QTimer>

namespace Ui {
class MapViewPage;
}

class MapViewPage : public QDialog
{
    Q_OBJECT

public:
    explicit MapViewPage(QWidget *parent = nullptr);
    ~MapViewPage();

private:
    Ui::MapViewPage *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsPixmapItem *character;
    KeyboardManager kbManager;
    QTimer timer;
    Character::Controller controller;

    void comboHandler(const QString&);

    //STeven SHIT
    CharacterManager* characterManager;
    WeaponManager* weaponManager;

public:
    void mouseMoveEvent(QMouseEvent*) override;
    void onMouseEvent(const QString& eName, const QPoint& p);
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
signals:
    void emitKeyboardPressed();
};

#endif // MAPVIEWPAGE_H
