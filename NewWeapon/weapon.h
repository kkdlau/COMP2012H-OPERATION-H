#ifndef WEAPON_H
#define WEAPON_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "qtimer.h"
#include "QRandomGenerator"
#include "qsequentialanimationgroup.h"

class Character;

enum WeaponType
{
    MELEE, RANGED
};

class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Weapon(WeaponType,int, QGraphicsItem*); //some area code may fix in future
    ~Weapon();
    void virtual Attack(int angle) = 0;
    void Equip(QGraphicsItem*);//havent been properly implemented
    void Unequip();
    void SetOwner(Character*);
    int GetWeaponId();
    WeaponType GetWeaponType();
    //temp implementation
    QString virtual WeaponDataText() = 0;
    void virtual InitializeAttackAnimation() = 0;
    void virtual OffsetWeaponGround() = 0;
    void virtual OffsetWeaponPickUp() = 0;

signals:
    void OnWeaponUpdate(QString);
protected:
    int weaponId = QRandomGenerator::global()->generate();
    QTimer timer;
    int attack = 0;
    QSequentialAnimationGroup attackAnimation;
    Character* owner;
private:
    WeaponType type;
};

#include "../character.h"


#endif // WEAPON_H
