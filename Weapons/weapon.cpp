#include "weapon.h"

// public
Weapon::~Weapon() = default;

char Weapon::get_id() const {return id;}
Weapon::WeaponCategory Weapon::get_weapon_category() const {return weapon_category;}
Weapon::WeaponType Weapon::get_weapon_type() const {return weapon_type;}
int Weapon::get_attack() const {return attack;}
int Weapon::get_attack_range() const {return attack_range;}
int Weapon::get_weight() const {return weight;}
int Weapon::get_max_quantity() const {return max_quantity;}

Character* Weapon::get_owner() const {return owner;}
Weapon::UseState Weapon::get_use_state() const {return use_state;}
Weapon::FocusState Weapon::get_focus_state() const {return focus_state;}
Weapon::ReadyState Weapon::get_ready_state() const {return ready_state;}

// protected
Weapon::Weapon(char id, WeaponCategory weapon_category, WeaponType weapon_type, int attack, int attack_range, int weight, int max_quantity, Character* owner)
    : id(id), weapon_category(weapon_category), weapon_type(weapon_type), attack(attack), attack_range(attack_range), weight(weight), max_quantity(max_quantity), owner(owner) {}
