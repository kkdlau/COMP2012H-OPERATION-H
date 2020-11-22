#include <cmath>
using std::abs;

#include "meleeweapon.h"

// public
MeleeWeapon::~MeleeWeapon() = default;
MeleeWeapon::ChargeState MeleeWeapon::get_charge_state() const {return charge_state;}

// protected
MeleeWeapon::MeleeWeapon(char id, WeaponType weapon_type, int attack, int attack_range, int weight) : Weapon(id, WEAPON_CATEGORY, weapon_type, attack, attack_range, weight, MAX_QUANTITY) {}

void MeleeWeapon::action_charge() {
    bool charge_success = true;
    // use a timer
    if (charge_success) {
        if (charge_state == ChargeState::CHARGED_LV1) {charge_state = ChargeState::CHARGED_LV2;}
        if (charge_state == ChargeState::UNCHARGED) {charge_state = ChargeState::CHARGED_LV1;}
    }
}

bool MeleeWeapon::within_attack_range(const Character* target) {
//	return (sqrt((owner->x - target->x)^2 + (owner->y - target->y)^2) <= attack_range);
    return (target != nullptr);
}
