#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H
#include "weapon.h"

class RangedWeapon : public Weapon
{
public:
    RangedWeapon(int attack, int attackSpeed, int reloadSpeed, int maxBullet,  QGraphicsItem*parent = nullptr);
    void virtual Attack() override;
    void virtual Reload();
private:
    void ResetShootState();
    void ResetReloadState();
    int attackSpeed;
    int reloadSpeed;
    bool isShooting = false;
    bool isReloading = false;
    int maxBullet;
    int currentBullet;
};

#endif // RANGEDWEAPON_H
