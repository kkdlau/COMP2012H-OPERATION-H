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
    /**
     * @brief Enemy constructor
     * @param map
     * @param moveSpeed
     * @param target
     */
    Enemy(Map* map, int moveSpeed = 100, Character *target = nullptr);
    Enemy(const Enemy &enemy) = delete;
    Enemy operator=(const Enemy& enemy) = delete;
    /**
     * @brief setDestination set the Enemy target to attack
     */
    void setDestination(Character*);
    /**
     * @brief The list of action done when the enemy has target
     */
    void action();
    /**
     * @brief move the Enemy to a designated area
     */
    void move();
    /**
     * @brief Enemy attack when it reaches certain distance between character
     */
    void attack();
    /**
     * @brief calculateRotation returns an angle between target
     * @return angle
     */
    qreal calculateRotation();
    /**
     * @brief Virtual function called after being damaged
     */
    virtual void Harmed();
    ~Enemy();
private:
    /**
     * @brief moveSpeed of the enemy movement
     */
    int moveSpeed;
    /**
     * @brief target of the Character being chased
     */
    Character* target;
    QTimer timer;
    /**
     * @brief healthBar of the enemy
     */
    int healthBar = 10;
    /**
     * @brief pathingList is the list of points an Enemy need to follow
     */
    QList<QPoint> pathingList;
};

#endif // ENEMY_H
