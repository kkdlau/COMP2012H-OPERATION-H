#include "shield.h"

// public
Shield::Shield(char id) : MeleeWeapon(id, WEAPON_TYPE, ATTACK, AR, WEIGHT){}
Shield::~Shield() = default;

bool Shield::is_broken() const {
    return (strength == 0);
}

void Shield::action_attack() const{
    return;
}

void Shield::action_defend(const int damage_received) {
    if (is_broken()) return;
    strength -= damage_received;
    if (strength < 0) {strength = 0;}
}

// private
void Shield::push_back(Character* target) {
    if (target != nullptr) return;
    return;
}

void Shield::restore_health() {
    strength = 100;
}
