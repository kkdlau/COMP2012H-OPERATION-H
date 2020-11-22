#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "weapon.h"

class MeleeWeapon : public Weapon {
public:
    enum class ChargeState {UNCHARGED, CHARGED_LV1, CHARGED_LV2};
    static const int CHARGE_TIME{1};  // in seconds
    static const WeaponCategory WEAPON_CATEGORY{WeaponCategory::MELEE};

    virtual ~MeleeWeapon();

    virtual void action_attack();
    virtual void action_charge() = 0;

    virtual bool within_attack_range(Character* target);

protected:
    MeleeWeapon(char id);
};

#endif // MELEEWEAPON_H
