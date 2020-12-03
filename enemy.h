#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "qtimer.h"
#include "character.h"
#include "QGraphicsPixmapItem"
#include "character.h"
#define MAX_HEALTH = 10;

class Enemy : public Character
{
    Q_OBJECT
    Q_PROPERTY(qreal moveX READ x WRITE setPositionX)
    Q_PROPERTY(qreal moveY READ y WRITE setPositionY)
public:
    Enemy(Map* map, int moveSpeed = 100, Character *target = nullptr);
    void setDestination(Character*);
    void unblock(MOVE_DIRECTION);
    void action();
    void move();
    void attack(QLineF distance);
    virtual void Harmed();
    ~Enemy();
private:
    int xUnblockOffset = 0;
    int yUnblockOffset = 0;
    int moveSpeed;
    Character* target;
    QTimer timer;
    int health = 10;
    QList<QPoint> pathingList;
    int stepIndex = 0;
};

#endif // ENEMY_H
