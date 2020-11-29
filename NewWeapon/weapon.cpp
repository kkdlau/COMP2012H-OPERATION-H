#include "weapon.h"

Weapon::Weapon(int attack, QGraphicsItem *parent = nullptr) :QGraphicsPixmapItem(parent), attack(attack)
{

}

void Weapon::Unequip()
{
    this->setParentItem(nullptr);
    equippedCharacter = nullptr;
}

void Weapon::Equip(QGraphicsItem * image, Character * character)
{
    this->setParentItem(image);
    equippedCharacter = character;
}
