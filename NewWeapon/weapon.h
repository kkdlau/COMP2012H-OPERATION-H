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
    /**
     * @brief SetOwner provides a function to set the Character class that uses this weapon
     */
    void SetOwner(Character*);
    /**
     * @brief GetWeaponId returns the randomly generated int for identification purposes
     * @return
     */
    int GetWeaponId();
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
    /**
     * @brief generate random weaponId for identification purposes
     */
    int weaponId = QRandomGenerator::global()->generate();
    QTimer timer;
    /**
     * @brief set the attack damage
     */
    int attack = 0;
    /**
     * @brief attackAnimation for the Weapon when attacking
     */
    QSequentialAnimationGroup attackAnimation;
    /**
     * @brief set the owner of the Character
     */
    Character* owner;
private:
    /**
     * @brief type of the Weapon
     */
    WeaponType type;
};

#include "../character.h"


#endif // WEAPON_H
