#include "meleeweapon.h"
#include "qdebug.h"

MeleeWeapon::MeleeWeapon(int attack,  int attackRange, int attackSpeed, QGraphicsItem* parent,QString image) : Weapon(attack, parent), attackRange(attackRange), attackSpeed(attackSpeed)
{
    setOffset(10, 0);
    InitializeAttackAnimation();
    connect(&attackAnimation, &QSequentialAnimationGroup::currentAnimationChanged, this, &MeleeWeapon::OnAttack);
    setPixmap(QPixmap(image));
}

void MeleeWeapon::Attack()
{
    if(!isAttack)
    {
        isAttack = true;
        timer.singleShot(attackSpeed, this, &MeleeWeapon::ResetAttack);
        attackAnimation.start();
    }
    else
    {
        qDebug()<<"COOLDOWN FOR ATTACK!";
    }
}

void MeleeWeapon::Charge()
{
    if (!isCharged)
    {
        isCharged = true;
    }
    else {
        qDebug() << "ALREADY CHARGED!";
    }
}

void MeleeWeapon::Skill()
{
    if (isCharged) {
        // do things like 2x attack, 2x speed
        timer.singleShot(skillTime, this, &MeleeWeapon::ResetCharge);
    }
    else {
        qDebug() << "NOT CHARGED. CANNOT USE SKILL!";
    }
}

void MeleeWeapon::OnAttack()
{
    qDebug()<<"doin animation REEEEEEEEEEEEEEEEEEEEEEEEEEEEE ";
    QList<QGraphicsItem*> collision = collidingItems();
    for(int i = 0; i < collision.length(); i++)
    {
        if(typeid(*(collision[i])) == typeid(Character))
        {
            qDebug()<<"INSERT HARMING FUCNTION TO CHARACTER";
        }
    }
}

void MeleeWeapon::InitializeAttackAnimation()
{
    QPropertyAnimation *startAnimation = new QPropertyAnimation(this, "pos");
    startAnimation->setDuration(attackSpeed/2);
    startAnimation->setStartValue(QPoint(0,0));
    startAnimation->setEndValue(QPoint(attackRange,0));
    attackAnimation.addAnimation(startAnimation);
    QPropertyAnimation *endAnimation = new QPropertyAnimation(this, "pos");
    endAnimation->setDuration(attackSpeed/2);
    endAnimation->setStartValue(QPoint(attackRange,0));
    endAnimation->setEndValue(QPoint(0,0));
    attackAnimation.addAnimation(endAnimation);

}

void MeleeWeapon::ResetAttack()
{
    isAttack = false;
}


void MeleeWeapon::ResetCharge()
{
    isCharged = false;
}
