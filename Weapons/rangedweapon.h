#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "weapon.h"

class RangedWeapon : public Weapon
{
public:
    static const WeaponCategory WEAPON_CATEGORY{WeaponCategory::RANGED};
    static const int MAX_QUANTITY{1};

    virtual ~RangedWeapon();

    int get_ammo() const;

protected:
    RangedWeapon(char id, WeaponType weapon_type, int attack, int attack_range, int weight);

    virtual void action_attack();
    virtual void action_reload();

    const int max_ammo{30};
    int ammo{max_ammo};
};

#endif // RANGEDWEAPON_H
