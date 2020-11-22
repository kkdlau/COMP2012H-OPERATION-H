#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "weapon.h"

class MeleeWeapon : public Weapon
{
public:
    enum class ChargeState {UNCHARGED, CHARGED_LV1, CHARGED_LV2};
    static const WeaponCategory WEAPON_CATEGORY{WeaponCategory::MELEE};
    static const int MAX_QUANTITY{1};

    virtual ~MeleeWeapon();

    ChargeState get_charge_state() const;

protected:
    MeleeWeapon(char id, WeaponType weapon_type, int attack, int attack_range, int weight);

    virtual void action_attack() const = 0;
    virtual void action_charge();

    virtual bool within_attack_range(const Character* target);

    ChargeState charge_state{ChargeState::UNCHARGED};
};

#endif // MELEEWEAPON_H
