#include "enemy.h"
#include "mapviewpage.h"
#include "qdebug.h"

Enemy::Enemy(Map* map, int moveSpeed, Character *target) : Character(moveSpeed, map), moveSpeed(moveSpeed), target(target)
{
    connect(&timer, &QTimer::timeout, this, &Enemy::action);
    connect(this, &Character::blockByObstacle, this, &Enemy::unblock);
    timer.start(300);
}

void Enemy::setDestination(Character* target)
{
    this->target = target;
}

void Enemy::action()
{
    QLineF drawLine(this->scenePos(), target->scenePos());
    move(drawLine);
    attack(drawLine);
}
void Enemy::move(QLineF drawLine)
{
    if(target != nullptr)
    {
        drawLine.setLength(moveSpeed/30);
        moveBy(drawLine.dx(), drawLine.dy());
    }
}

void Enemy::attack(QLineF drawLine)
{
    if(currentWeapon != nullptr && drawLine.length() < 5)
    {
        shoot();
    }
}

void Enemy::unblock(MOVE_DIRECTION direction)
{
    QLineF drawLine(this->scenePos(), target->scenePos());
    if(MOVE_DIRECTION::UP == direction || MOVE_DIRECTION::DOWN == direction)
    {
        moveBy(drawLine.dx()*1.5, 0);
    }
    else
    {
        moveBy(0,drawLine.dy()*1.5);
    }

}

void Enemy::Harmed() //this class should inherit character for usability
{
    qDebug()<<"IM GETTING HIT BABY WOOshjdkfjkalfhjakldshk";
    if(characterHealth <= 0)
    {
        dequipWeapon();
        emit deadSignal(this);
    }
}

Enemy::~Enemy()
{
    disconnect(&timer, &QTimer::timeout, this, &Enemy::action);
    disconnect(this, &Character::blockByObstacle, this, &Enemy::unblock);
    timer.stop();
}
