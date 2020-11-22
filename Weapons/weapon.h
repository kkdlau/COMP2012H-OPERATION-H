#ifndef WEAPON_H
#define WEAPON_H

#include "character.h"

class Weapon {
public:
    enum class WeaponCategory {MELEE, RANGED, THROWING};
    enum class WeaponType {KNIFE, SWORD, CLAWS, SHIELD, HANDGUN, MACHINEGUN, RIFLE, GRENADE};
    enum class UseState {NOT_HELD, HELD};  // UseState HELD = held by a player
    enum class FocusState {NOT_FOCUS, FOCUS};  // FocusState FOCUS = 1st weapon in hand
    enum class ReadyState {NOT_READY, READY};  // ReadyState READY = weapon can attack (i.e. have ammo). Melee is always READY

    virtual ~Weapon();

    Character* get_owner() const;

    char get_id() const;
    WeaponType get_weapon_type() const;
    int get_attack_range() const;
    int get_weight() const;

    Character* owner{nullptr};

protected:
    Weapon(char id, WeaponCategory weapon_category, WeaponType weapon_type, int attack, int attack_range, int weight, int max_quantity, Character* owner);

    const char id;
    const WeaponCategory weapon_category;
    const WeaponType weapon_type;
    const int attack;
    const int attack_range;
    const int weight;
    const int max_quantity;

    UseState use_state{UseState::NOT_HELD};
    FocusState focus_state{FocusState::NOT_FOCUS};
    ReadyState ready_state{ReadyState::READY};
    int quantity{0};
};

#endif // WEAPON_H
