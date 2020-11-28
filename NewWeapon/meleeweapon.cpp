#include "meleeweapon.h"
#include "qdebug.h"

MeleeWeapon::MeleeWeapon(int attack, QGraphicsItem* parent, int attackRange, int attackSpeed, QString image) : Weapon(attack, parent), attackRange(attackRange), attackSpeed(attackSpeed)
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

void MeleeWeapon::OnAttack()
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
