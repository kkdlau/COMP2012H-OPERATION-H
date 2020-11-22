#include "character.h"

Character::Character(QString name, int attack, int health) : playerName(name), attack(attack), health(health)
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

bool Character::is_alive(){
    return characterHealth > 0;
}
