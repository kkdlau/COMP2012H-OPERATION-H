#include "character.h"

Character::Character(int stepValue): stepValue{stepValue} {

}

Character::Character(QString name, int health, int stepValue) : characterName(name), characterHealth(health), stepValue{stepValue}
{

}

Character::Character(const QStringList data, int stepValue): stepValue{stepValue}
{

}

QPointF Character::getPosition() const {
    return pos();
}

void Character::moveBy(qreal x, qreal y) {
   QPointF newPos = this->pos() + QPoint(x, y);
}

//Character operator=(const Character& input) {

//}

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
