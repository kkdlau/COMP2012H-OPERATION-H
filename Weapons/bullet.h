#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "QGraphicsPixmapItem"
#include "qtimer.h"

class Bullet : public QObject,public QGraphicsPixmapItem
{

public:
    Bullet(int damage, int angle, int mapHeight, int x, int y);
    void move();
private:
    const int damage;
    const int angle;
    const int mapHeight;
    const int bulletSpeed = 3;
    QTimer *timer;
};

#endif // BULLET_H
