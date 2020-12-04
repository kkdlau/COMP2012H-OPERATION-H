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
    /**
     * @brief Weapon abstract class
     */
    Weapon(WeaponType,int, QGraphicsItem*); //some area code may fix in future
    ~Weapon();
    /**
     * @brief Attack pure virtual function acts as a placeholder for Attack implementation
     * @param angle for projectile-based weapon
     */
    void virtual Attack(int angle) = 0;
//    void Equip(QGraphicsItem*);//havent been properly implemented
//    void Unequip();
    /**
     * @brief SetOwner provides a function to set the Character class that uses this weapon
     */
    void SetOwner(Character*);
    /**
     * @brief GetWeaponId returns the randomly generated int for identification purposes
     * @return
     */
    int GetWeaponId();
//    WeaponType GetWeaponType();
    //temp implementation
    /**
     * @brief WeaponDataText provide text for UI purposes
     * @return
     */
    QString virtual WeaponDataText() = 0;
    /**
     * @brief InitializeAttackAnimation is a pure virtual function for derived class to add animation when attacking
     */
    void virtual InitializeAttackAnimation() = 0;
    /**
     * @brief OffsetWeaponGround provides the weapon offset when placed on ground(GridMap)
     */
    void virtual OffsetWeaponGround() = 0;
    /**
     * @brief OffsetWeaponPickUp provides the weapon offset when equipped by the character
     */
    void virtual OffsetWeaponPickUp() = 0;

signals:
    /**
     * @brief OnWeaponUpdate provides signal to update the UI text(ItemMap)
     */
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
