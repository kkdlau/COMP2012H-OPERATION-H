#include "enemy.h"
#include "mapviewpage.h"
#include "qdebug.h"

Enemy::Enemy(Map* map, int moveSpeed, Character *target) : Character(moveSpeed, map), moveSpeed(moveSpeed), target(target)
{
    connect(&timer, &QTimer::timeout, this, &Enemy::Move);
    connect(this, &Character::blockByObstacle, this, &Enemy::Unblock);
    timer.start(100);
}

void Enemy::SetDestination(Character* target)
{
    this->target = target;
}

void Enemy::Move()
{
    if(target != nullptr)
    {
        QLineF drawLine(this->scenePos(), target->scenePos());
        drawLine.setLength(moveSpeed/30);
        moveBy(drawLine.dx(), drawLine.dy());
    }
}

void Enemy::Unblock(MOVE_DIRECTION direction)
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
    if(health <= 0)
    {
        delete this;
    }
}
