#include "character.h"

character::character(QString name, int attack, int health) : playerName(name), attack(attack), health(health)
{

}

character::character(const QStringList data)
{

}

character::~character(){};

QString character::get_name()
{
    return playerName;
}

int character::get_attack()
{
    return attack;
}
