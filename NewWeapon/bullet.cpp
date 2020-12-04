#include "bullet.h"
#include "QtMath"
#include <QGraphicsScene>

Bullet::Bullet(int damage, int angle, QGraphicsItem* owner): damage(damage), angle(angle), owner(owner)
{
    setPixmap(QPixmap(":bullet"));
    connect(&timer, &QTimer::timeout, this, &Bullet::move);
    timer.start(50);
}

Bullet::~Bullet()
{
    disconnect(&timer, &QTimer::timeout, this, &Bullet::move);
    timer.stop();
}

void Bullet::move()
{
    float radian = qDegreesToRadians((float)angle);
    float yOffset = bulletSpeed * qSin(radian);
    float xOffset =  bulletSpeed * qCos(radian);
    setPos(x()+xOffset, y()+yOffset);
    QList<QGraphicsItem*> collision = collidingItems();
    for(int i = 0; i < collision.length(); i++)
    {
        Character* target = dynamic_cast<Character*>(collision[i]->parentItem());
        if(target && target != owner)
        {
            target->DealDamage(damage);
            setVisible(false);
            return;
        }
    }
    if(--lifeSpan <= 0)
    {
        disconnect(&timer, &QTimer::timeout, this, &Bullet::move);
        timer.stop();
        setVisible(false);
    }
}
