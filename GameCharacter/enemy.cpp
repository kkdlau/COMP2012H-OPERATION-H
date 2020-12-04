#include "enemy.h"
#include "mapviewpage.h"
#include "qdebug.h"
#include <QtMath>
#include "Pathing/astar.h"

Enemy::Enemy(Map* map, int moveSpeed, Character *target) : Character(charType::ENEMY, moveSpeed, map), moveSpeed(moveSpeed), target(target)
{
    connect(&timer, &QTimer::timeout, this, &Enemy::action);
    connect(this, &Character::blockByObstacle, this, &Enemy::unblock);
    setMoveSpd(5);
    timer.start(50);
}

void Enemy::setDestination(Character* target)
{
    this->target = target;
}

void Enemy::action()
{
    if(target != nullptr && target->is_alive())
    {
        setRotation(calculateRotation());
        move();
        attack();
    }
    else if (target != nullptr && !target->is_alive())
    {
        target = nullptr;
    }
}

void Enemy::move()
{
    if(target != nullptr)
    {
        if(pathingList.isEmpty())
        {
            AStar pathing{*presetMap};
            pathingList = pathing.search(getGridPos(), target->getGridPos());
        }
        else
        {

            moveTo(pathingList[1]);
            if(pathingList[1] == getGridPos() && isPerfectCenterize())
            {
                if(!pathingList.isEmpty()) pathingList.clear();
                AStar pathing{*presetMap};
                pathingList = pathing.search(getGridPos(), target->getGridPos());
            }
        }

    }
}

void Enemy::attack()
{
    QLineF distance(getGridPos(), target->getGridPos());
    if(currentWeapon != nullptr && distance.length() < 16)
    {
        Character::attack();
    }
}

void Enemy::unblock(MOVE_DIRECTION direction)
{
    QLineF drawLine(this->scenePos(), target->scenePos());
    if(MOVE_DIRECTION::UP == direction)
    {
        moveBy(0, 0.5);
    }
    else if (MOVE_DIRECTION::DOWN == direction)
    {
        moveBy(0,-0.5);
    }
    else if (MOVE_DIRECTION::LEFT == direction)
    {
         moveBy(0.5,0);
    }
    else
    {
        moveBy(-0.5,0);
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

qreal Enemy::calculateRotation()
{
    if(target != nullptr)
    {
        QLineF distance(pos(), target->pos());
        float rad = qAtan2(distance.dy(), distance.dx());
        return qRadiansToDegrees(rad);
    }
    else return 0;
}
