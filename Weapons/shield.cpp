#include "shield.h"

// public
Shield::Shield(char id, Character* owner) : MeleeWeapon(id, WEAPON_TYPE, ATTACK, AR, WEIGHT, owner){}
Shield::~Shield() = default;

void Shield::action_attack() const{
    int a = 0;
    return;
}

// private
void Shield::restore_health() {
    strength = 100;
}
