#include "weapon.h"

Weapon::Weapon(WeaponType weaponType, int attack, QGraphicsItem *parent = nullptr) :QGraphicsPixmapItem(parent), attack(attack), type(weaponType)
{

}

Weapon::~Weapon(){}

//void Weapon::Unequip()
//{
//    QPointF newPos(this->parentItem()->scenePos());
//    this->setParentItem(nullptr);
//    this->setPos(newPos);

//}
//void Weapon::Equip(QGraphicsItem *image)
//{
//    this->setParentItem(image);
//    this->setPos(0,0);
//}


void Weapon::SetOwner(Character* owner)
{
    this->owner = owner;
}

int Weapon::GetWeaponId()
{
    return weaponId;
}

//WeaponType Weapon::GetWeaponType()
//{
//    return type;
//}
