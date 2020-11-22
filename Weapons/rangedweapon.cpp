#include "rangedweapon.h"

// public
RangedWeapon::~RangedWeapon() = default;
int RangedWeapon::get_ammo() const {return ammo;}

// protected
RangedWeapon::RangedWeapon(char id, WeaponType weapon_type, int attack, int attack_range, int weight, Character* owner) : Weapon(id, WEAPON_CATEGORY, weapon_type, attack, attack_range, weight, MAX_QUANTITY, owner) {}

void RangedWeapon::action_attack() {
//    shoot();
    --ammo;
}

void RangedWeapon::action_reload() {
    ammo = max_ammo;
}
