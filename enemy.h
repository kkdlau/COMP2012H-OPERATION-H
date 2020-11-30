#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include "qtimer.h"
#include "character.h"
#include "QGraphicsPixmapItem"
#define MAX_HEALTH = 10;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(int moveSpeed = 100, Character *target = nullptr);
    void SetDestination(Character*);
    void Move();
    void Harmed();
private:
    int moveSpeed;
    Character* target;
    QTimer timer;
    int health = 10;
};

#endif // ENEMY_H
