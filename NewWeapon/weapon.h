#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "qtimer.h"
#include "character.h"
class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Weapon(int, QGraphicsItem*); //some area code may fix in future
    void virtual Attack() = 0;
    void Equip(QGraphicsItem*, Character*);//havent been properly implemented
    void Unequip();
protected:
    QTimer timer;
    Character* equippedCharacter;
    int attack = 0;
};

#endif // WEAPON_H
