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
    return playerName;
}

int Character::get_attack() const
{
    return attack;
}

int Character::get_health() const
{
    return health;
}
