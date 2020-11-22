#ifndef HANDGUN_H
#define HANDGUN_H

#include "rangedweapon.h"

class HandGun : public RangedWeapon
{
public:
    static const WeaponType WEAPON_TYPE{WeaponType::HANDGUN};
    static const int ATTACK{3};
    static const int AR{10};
    static const int WEIGHT{1};
    static const int MAX_AMMO{12};

    HandGun(char id);
    virtual ~HandGun();

};

#endif // HANDGUN_H
