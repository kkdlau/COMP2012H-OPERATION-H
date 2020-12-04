#include "weapon.h"

Weapon::Weapon(WeaponType weaponType, int attack, QGraphicsItem *parent = nullptr) :QGraphicsPixmapItem(parent), attack(attack), type(weaponType)
{

}

Weapon::~Weapon(){}


void Weapon::SetOwner(Character* owner)
{
    this->owner = owner;
}

int Weapon::GetWeaponId()
{
    return weaponId;
}

WeaponType Weapon::GetWeaponType()
{
    return type;
}
