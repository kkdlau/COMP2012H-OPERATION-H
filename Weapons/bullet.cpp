#include "bullet.h"
#include "QtMath"
#include <QGraphicsScene>

Bullet::Bullet(int damage, int angle, int x, int y, Character* owner): damage(damage), angle(angle), owner(owner)
{
    owner->scene()->addItem(this);
    setPos(x,y);
    setPixmap(QPixmap(":bullet"));
    connect(&timer, &QTimer::timeout, this, &Bullet::move);
    timer.start(50);
}

void Bullet::move()
{
    int angleSection = angle/ 90;
    float radian = qDegreesToRadians((float)angle);
    float yOffset = angleSection % 2 == 0? bulletSpeed * qSin(radian) : bulletSpeed * qCos(radian);
    float xOffset = angleSection % 2 == 0? bulletSpeed * qCos(radian) : bulletSpeed * qSin(radian);
    qDebug()<<"X: "<<x()<<"/"<<xOffset<<"Y: "<<y()<<"/"<<yOffset;
    setPos(x()+xOffset, y()+yOffset);
    QList<QGraphicsItem*> collision = collidingItems();
    for(int i = 0; i < collision.length(); i++)
    {
        if(typeid(*(collision[i])) == typeid(Character) && collision[i] != owner)
        {
            qDebug()<<"ENEMY HIT U FUCKIN CUNT";
        }
    }
    if(--lifeSpan <= 0)
    {
        delete this;
    }
}
