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
#include "NewWeapon/rangedweapon.h"

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

    void comboHandler(const QString&);
    RangedWeapon *testWeapon;

public:
    void mouseMoveEvent(QMouseEvent*) override;
    void onMouseEvent(const QString& eName, const QPoint& p);
signals:
    void keyPressEvent(QKeyEvent*) ;
    void keyReleaseEvent(QKeyEvent*) ;
};

#endif // MAPVIEWPAGE_H
