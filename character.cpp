#include "character.h"

Character::Character(){

}

Character::Character(QString name, int health) : characterName(name), characterHealth(health)
{

}

Character::Character(const QStringList data)
{

}

Character::~Character(){};

QString Character::get_name() const
{
    return characterName;
}

int Character::get_health() const
{
    return characterHealth;
}

void Character::set_name(QString name) {
    characterName = name;
}

void Character::set_health(int health) {
    characterHealth = health;
}

bool Character::is_alive() const{
    return characterHealth > 0;
}

void Character::shoot() {
//    if (curWeapon.getWeaponType()) {
//        return;
//    }
}
