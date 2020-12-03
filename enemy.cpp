#include "enemy.h"
#include "mapviewpage.h"
#include "qdebug.h"
#include <QtMath>
#include "Pathing/astar.h"

Enemy::Enemy(Map* map, int moveSpeed, Character *target) : Character(moveSpeed, map), moveSpeed(moveSpeed), target(target)
{
    connect(&timer, &QTimer::timeout, this, &Enemy::action);
    connect(this, &Character::blockByObstacle, this, &Enemy::unblock);
    timer.start(150);
}

void Enemy::setDestination(Character* target)
{
    this->target = target;
}

void Enemy::action()
{
    if(target != nullptr)
    {
        AStar pathing{*presetMap};
        qDebug()<<"POSITIONS ORIGIN: "<<(pos()/32).toPoint()<< "TARGET: "<<(target->pos()/32).toPoint();

        QList<QPoint> pathToTake = pathing.search((pos()/32).toPoint(), (target->pos()/32).toPoint());
        qDebug()<<"LIST:"<<pathToTake;
        presetMap->drawPath(pathToTake);
        QLineF drawLine(this->scenePos(), target->scenePos());
        setRotation(qRadiansToDegrees(qAtan2(drawLine.dx(), drawLine.dy())) * -1 + 90);
        move(pathToTake[1]*32);
//        attack(drawLine);
    }

}
void Enemy::move(QPoint point)
{
    if(target != nullptr)
    {   QLineF pathLine(this->scenePos(), point);
        pathLine.setLength(5);
        moveBy(pathLine.dx(), pathLine.dy());
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
