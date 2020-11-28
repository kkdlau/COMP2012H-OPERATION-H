#include "testmelee.h"
#include "qdebug.h"
#include "character.h"
testmelee::testmelee(QGraphicsItem* something) : QGraphicsPixmapItem(something)
{
    test = new QPropertyAnimation(this, "pos");
    test->setDuration(250);
    test->setStartValue(QPoint(0,0));
    test->setEndValue(QPoint(10,10));
    test->setTargetObject(this);
    sampleAnimation.addAnimation(test);
    QPropertyAnimation *gay = new QPropertyAnimation(this, "pos");
    gay->setDuration(250);
    gay->setEndValue(QPoint(0,0));
    gay->setStartValue(QPoint(10,10));
    gay->setTargetObject(this);
    sampleAnimation.addAnimation(gay);
    setPixmap(QPixmap(":knife"));
    connect(&sampleAnimation, &QSequentialAnimationGroup::currentAnimationChanged, this, &testmelee::animationDone);
}

void testmelee::attack()
{
    sampleAnimation.start();
}

void testmelee::animationDone()
{
    qDebug()<<"doin animation REEEEEEEEEEEEEEEEEEEEEEEEEEEEE ";
    QList<QGraphicsItem*> collision = collidingItems();
    for(int i = 0; i < collision.length(); i++)
    {
        if(typeid(*(collision[i])) == typeid(Character))
        {
            dynamic_cast<Character*>(collision[i])->on_hit();
        }
    }

}
