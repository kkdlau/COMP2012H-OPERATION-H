#include "bullet.h"
#include "QtMath"
#include <QGraphicsScene>

Bullet::Bullet(int damage, int angle, int x, int y, QGraphicsItem* owner): damage(damage), angle(angle), owner(owner)
{
    setPos(x,y);
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
    int angleSection = angle/ 90;
    float radian = qDegreesToRadians((float)angle);
    float yOffset = angleSection % 2 == 0? bulletSpeed * qSin(radian) : bulletSpeed * qCos(radian);
    float xOffset = angleSection % 2 == 0? bulletSpeed * qCos(radian) : bulletSpeed * qSin(radian);
    setPos(x()+xOffset, y()+yOffset);
    QList<QGraphicsItem*> collision = collidingItems();
    for(int i = 0; i < collision.length(); i++)
    {
        Character* target = dynamic_cast<Character*>(collision[i]->parentItem());
        if(target && target != owner)
        {
            target->DealDamage(damage);
            setVisible(false); //ask danny for shit
            return;
        }
    }
    if(--lifeSpan <= 0)
    {
        qDebug()<<"I DIED";
        delete this;
    }
}
