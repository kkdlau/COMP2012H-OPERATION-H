#include "character.h"

character::character(QString name, int attack, int health) : playerName(name), attack(attack), health(health)
{

}

character::character(const QStringList data)
{

}

character::~character(){};

QString character::get_name() const
{
    return playerName;
}

int character::get_attack() const
{
    return attack;
}
