#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H
#include "weapon.h"

class RangedWeapon : public Weapon
{
public:
    /**
     * @brief RangedWeapon constructor
     * @param attack sets the damage for the Bullet
     * @param attackSpeed sets how fast does the gun Shoot for whole maxBullet
     * @param reloadSpeed sets how fast does it reload when the currentBullet is empty
     * @param maxBullet sets the maximum currentBullet
     * @param parent sets the RangedWeapon QGraphicsItem Parent
     */
    RangedWeapon(int attack, int attackSpeed, int reloadSpeed, int maxBullet,  QGraphicsItem*parent = nullptr);
    /**
     * @brief Attack implementation for the RangedWeapon
     * @param angle for bullet angle travel
     */
    void virtual Attack(int angle) override;
    /**
     * @brief Reload is a virtual function on how to reset the currentBullet
     */
    void virtual Reload();
    /**
     * @brief WeaponDataText implementation for RangedWeapon
     * @return QString for ItemFrame QLabel
     */
    QString virtual WeaponDataText() override;
    /**
     * @brief InitializeAttackAnimation implementation for RangedWeapon recoil animation
     */
    void virtual InitializeAttackAnimation() override;
    /**
     * @brief OffsetWeaponGround implementation for RangedWeapon when placed on ground
     */
    void virtual OffsetWeaponGround() override;
    /**
     * @brief OffsetWeaponPickUp implementation for RangedWeapon when picked up
     */
    void virtual OffsetWeaponPickUp() override;
private:
    /**
     * @brief ResetShootState reset the isShoot state to false
     */
    void ResetShootState();
    /**
     * @brief ResetReloadState reset the isReloading state to false
     */
    void ResetReloadState();
    /**
     * @brief attackSpeed set the RangedWeapon attack speed (per Bullet)
     */
    int attackSpeed;
    /**
     * @brief reloadSpeed set the RangedWeapon reload speed
     */
    int reloadSpeed;
    /**
     * @brief isShooting controls if the weapon Attack already
     */
    bool isShooting = false;
    /**
     * @brief isReloading controls if the weapon is reloading
     */
    bool isReloading = false;
    /**
     * @brief maxBullet set the max capacity of the currentBullet
     */
    int maxBullet;
    /**
     * @brief currentBullet tells the current amount of bullet that can be shot
     */
    int currentBullet;
};

#endif // RANGEDWEAPON_H
