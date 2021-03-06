#include "rangedweapon.h"
#include "NewWeapon/bullet.h"
#include "GameCharacter/character.h"
RangedWeapon::RangedWeapon(int attack, int attackSpeed, int reloadSpeed,int maxBullet, QGraphicsItem *parent): Weapon(WeaponType::RANGED, attack,parent), attackSpeed(attackSpeed), reloadSpeed(reloadSpeed), maxBullet(maxBullet), currentBullet(maxBullet)
{
    setPixmap(QPixmap(":gun.png"));
    InitializeAttackAnimation();
}

void RangedWeapon::Attack(int angle)
{
    if(!isShooting && currentBullet > 0)
    {
        --currentBullet;
        isShooting = true;
        Bullet *bulletShot = new Bullet(5, angle, owner);
        bulletShot->setParentItem(owner->parentItem());
        bulletShot->setPos(owner->pos());//fix this
        qDebug()<<"POS CHECK "<<owner->pos();
        attackAnimation.start();
        timer.singleShot(attackSpeed/maxBullet, this, &RangedWeapon::ResetShootState);
        emit OnWeaponUpdate(WeaponDataText());


    }
    else if (currentBullet <= 0)
    {
        Reload();
    }
}

void RangedWeapon::Reload()
{
    if(!isReloading)
    {
        emit OnWeaponUpdate("RELOADING");
        isReloading = true;
        timer.singleShot(reloadSpeed, this, &RangedWeapon::ResetReloadState);
    }
}

void RangedWeapon::ResetShootState()
{
    isShooting = false;
}

void RangedWeapon::ResetReloadState()
{
    currentBullet = maxBullet;
    emit OnWeaponUpdate(WeaponDataText());
    isReloading = false;
}


QString RangedWeapon::WeaponDataText()
{
    return QString::number(currentBullet) + "/" + QString::number(maxBullet);
}

void RangedWeapon::InitializeAttackAnimation()
{
    QPropertyAnimation *startAnimation = new QPropertyAnimation(this, "pos");
    startAnimation->setDuration(attackSpeed/2);
    startAnimation->setStartValue(QPoint(0,0));
    startAnimation->setEndValue(QPoint(-5,0));
    attackAnimation.addAnimation(startAnimation);
    QPropertyAnimation *endAnimation = new QPropertyAnimation(this, "pos");
    endAnimation->setDuration(attackSpeed/2);
    endAnimation->setStartValue(QPoint(-5,0));
    endAnimation->setEndValue(QPoint(0,0));
    attackAnimation.addAnimation(endAnimation);

}

void RangedWeapon::OffsetWeaponPickUp()
{
    setOffset(10,0);
}

void RangedWeapon::OffsetWeaponGround()
{
    setOffset(0,0);
}
