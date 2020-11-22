#ifndef SHIELD_H
#define SHIELD_H

#include "meleeweapon.h"

class Shield final: public MeleeWeapon
{
public:
    static const WeaponType WEAPON_TYPE{WeaponType::SHIELD};
    static const int ATTACK{0};
    static const int AR{1};
    static const int WEIGHT{1};
    static const int PUSHBACK_DISTANCE{10};

    Shield(char id, Character* owner);
    virtual ~Shield();

    virtual void action_attack() const override;

private:
    int strength{100};
    void restore_health();
};

#endif // SHIELD_H
