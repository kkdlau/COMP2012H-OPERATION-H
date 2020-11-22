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

    bool is_broken() const;

    virtual void action_attack_uncharged() const override;
    virtual void action_attack_charged_lv1() const override;
    virtual void action_attack_charged_lv2() const override;
    void action_defend(const int damage_received);

private:
    int strength{100};
    void push_back(Character* target);
    void restore_health();
};

#endif // SHIELD_H
