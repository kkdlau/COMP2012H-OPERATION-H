#ifndef TESTMELEE_H
#define TESTMELEE_H
#include "QGraphicsPixmapItem"
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QObject>

class testmelee :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    testmelee(QGraphicsItem *);
    void attack();
    void animationDone();
    QSequentialAnimationGroup sampleAnimation;
    QPropertyAnimation *test;

};

#endif // TESTMELEE_H
