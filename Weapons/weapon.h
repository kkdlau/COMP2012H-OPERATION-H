#ifndef WEAPON_H
#define WEAPON_H

#include "character.h"

class Weapon : public QGraphicsItem
{
public:
    enum class WeaponCategory {MELEE, RANGED, THROWING};
    enum class WeaponType {KNIFE, SWORD, CLAWS, SHIELD, HANDGUN, MACHINEGUN, RIFLE, GRENADE};
    enum class UseState {NOT_HELD, HELD};
    enum class FocusState {NOT_FOCUS, FOCUS};
    enum class ReadyState {NOT_READY, READY};

    virtual ~Weapon();

    char get_id() const;
    WeaponCategory get_weapon_category() const;
    WeaponType get_weapon_type() const;
    int get_attack() const;
    int get_attack_range() const;
    int get_weight() const;
    int get_max_quantity() const;

    Character* get_owner() const;
    UseState get_use_state() const;
    FocusState get_focus_state() const;
    ReadyState get_ready_state() const;

protected:
    Weapon(char id, WeaponCategory weapon_category, WeaponType weapon_type, int attack, int attack_range, int weight, int max_quantity, Character* owner);

    virtual void action_attack() const = 0;

    const char id;
    const WeaponCategory weapon_category;
    const WeaponType weapon_type;
    const int attack;
    const int attack_range;
    const int weight;
    const int max_quantity;

    Character* owner{nullptr};
    UseState use_state{UseState::NOT_HELD};
    FocusState focus_state{FocusState::NOT_FOCUS};
    ReadyState ready_state{ReadyState::READY};
    int quantity{max_quantity};
};

#endif // WEAPON_H
