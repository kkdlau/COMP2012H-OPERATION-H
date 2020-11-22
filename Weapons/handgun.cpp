#include "handgun.h"

HandGun::HandGun(char id, Character* owner) : RangedWeapon(id, WEAPON_TYPE, ATTACK, AR, WEIGHT, owner) {}
HandGun::~HandGun() = default;
