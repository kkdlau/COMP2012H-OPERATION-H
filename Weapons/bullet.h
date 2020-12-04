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
    /**
     * @brief Bullet constructor creates the bullet when RangedWeapon attack
     * @param damage sets the bullet damage when hit Character*
     * @param angle sets the bullet angle tragectory
     * @param x set the X position in the map
     * @param y set the Y position in the map
     * @param owner sets the pointer of the RangedWeapon owner to prevent self collsiion
     */
    Bullet(int damage, int angle, int x, int y, QGraphicsItem* owner);
    Bullet(const Bullet &bullet) = delete;
    Bullet operator=(const Bullet& bullet) = delete;
    ~Bullet();
    /**
     * @brief move the bullet everytime the timer is called
     */
    void move();
private:
    /**
     * @brief owner sets the RangedWeapon owner
     */
    QGraphicsItem * owner;
    /**
     * @brief bullet damage when collide with Character*
     */
    const int damage;
    /**
     * @brief angle tragectory of where the bullet move
     */
    const int angle;
    /**
     * @brief bulletSpeed set how fast the bullet being shot
     */
    const int bulletSpeed = 3;
    /**
     * @brief lifeSpan set the bullet lifespan before destroying itself
     */
    int lifeSpan = 100;
    QTimer timer;
};

#endif // BULLET_H
