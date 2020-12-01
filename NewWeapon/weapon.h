#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "qtimer.h"
#include "QRandomGenerator"

class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Weapon(int, QGraphicsItem*); //some area code may fix in future
    void virtual Attack(int angle) = 0;
    void Equip(QGraphicsItem*);//havent been properly implemented
    void Unequip();
    int GetWeaponId();
protected:
    int weaponId = QRandomGenerator::global()->generate();
    QTimer timer;
    int attack = 0;
};

#endif // WEAPON_H
