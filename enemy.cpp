#include "enemy.h"
#include "mapviewpage.h"

Enemy::Enemy(int moveSpeed, Character *target) : moveSpeed(moveSpeed), target(target)
{
    setPixmap(QPixmap(":knife"));
    connect(&timer, &QTimer::timeout, this, &Enemy::Move);
    timer.start(1000/60);
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
        drawLine.setLength(moveSpeed/60);
        setPos(x() + drawLine.dx(), y() + drawLine.dy());
    }
}

void Enemy::Harmed(int damage) //this class should inherit character for usability
{
    health -= damage;
    if(health <= 0)
    {
        delete this;
    }
}
