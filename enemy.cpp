#include "enemy.h"
#include "mapviewpage.h"
#include "qdebug.h"
#include <QtMath>
#include "Pathing/astar.h"

Enemy::Enemy(Map* map, int moveSpeed, Character *target) : Character(moveSpeed, map), moveSpeed(moveSpeed), target(target)
{
    connect(&timer, &QTimer::timeout, this, &Enemy::action);
    connect(this, &Character::blockByObstacle, this, &Enemy::unblock);
    timer.start(200);
    setPos(QPointF{32* 3 + 16, 32 * 5 + 16});
}

void Enemy::setDestination(Character* target)
{
    this->target = target;
}

void Enemy::action()
{
    if(target != nullptr)
    {
        move();
//        AStar pathing{*presetMap};
//        qDebug()<<"POSITIONS ORIGIN: "<<(pos()/32).toPoint()<< "TARGET: "<<(target->pos()/32).toPoint();

//        QList<QPoint> pathToTake = pathing.search((pos()/32).toPoint(), (target->pos()/32).toPoint());
//        qDebug()<<"LIST:"<<pathToTake;
//        presetMap->drawPath(pathToTake);
//        QLineF drawLine(this->scenePos(), target->scenePos());
//        setRotation(qRadiansToDegrees(qAtan2(drawLine.dx(), drawLine.dy())) * -1 + 90);
//        move(pathToTake[1]*32);
//        attack(drawLine);
    }

}
void Enemy::move()
{
    if(target != nullptr)
    {
        if(pathingList.isEmpty())
        {
            AStar pathing{*presetMap};
            pathingList = pathing.search((pos()/32).toPoint(), (target->pos()/32).toPoint());
            qDebug()<<"LIST GENERATED "<< pathingList;
        }
        else
        {
            moveTo(pathingList[0]);
            qDebug()<<"CURR POS : "<< getGridPos();
            qDebug()<<"Target POS : "<< pathingList[0];
            if(pathingList[0] == getGridPos())
            {
                if(!pathingList.isEmpty())
                {
                    qDebug()<<"DELETING POS : "<< pathingList[0];
                    pathingList.removeFirst();
                }
                else
                {
                    qCritical()<<"EMPTY LIST BYPASSED?";
                }
            }
        }

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
