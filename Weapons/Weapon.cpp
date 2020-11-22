#include "weapon.h"

Weapon::~Weapon() = default;

char Weapon::get_id() const {return id;}
Weapon::WeaponType Weapon::get_weapon_type() const {return weapon_type;}
int Weapon::get_attack_range() const {return attack_range;}
int Weapon::get_weight() const {return weight;}

// protected
Weapon::Weapon(char id, WeaponCategory weapon_category, WeaponType weapon_type, int attack, int attack_range, int weight, int max_quantity, Character* owner)
    :id(id), weapon_category(weapon_category), weapon_type(weapon_type),
      attack(attack), attack_range(attack_range), weight(weight),
      max_quantity(max_quantity), owner(owner) {}
