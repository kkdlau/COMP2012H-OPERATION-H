#include "handgun.h"

HandGun::HandGun(char id) : RangedWeapon(id, WEAPON_TYPE, ATTACK, AR, WEIGHT) {}
HandGun::~HandGun() = default;

void action_attack() {
    return;
}
