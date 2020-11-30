#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "qtimer.h"
#include "character.h"
#include "qdebug.h"
class Bullet : public QObject,public QGraphicsPixmapItem
{

public:
    Bullet(int damage, int angle, int x, int y);
    void move();
private:
    const int damage;
    const int angle;
    const int bulletSpeed = 3;
    int lifeSpan = 100;
    QTimer timer;
};

#endif // BULLET_H
