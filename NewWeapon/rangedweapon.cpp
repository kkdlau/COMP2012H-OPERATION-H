#include "rangedweapon.h"
#include "Weapons/bullet.h"
#include "character.h"
RangedWeapon::RangedWeapon(int attack, int attackSpeed, int reloadSpeed,int maxBullet, QGraphicsItem *parent): Weapon(attack,parent), attackSpeed(attackSpeed), reloadSpeed(reloadSpeed), maxBullet(maxBullet), currentBullet(maxBullet)
{
    setPixmap(QPixmap(":gun.png"));
}

void RangedWeapon::Attack(int angle)
{
    if(!isShooting && currentBullet > 0)
    {
        --currentBullet;
        qDebug()<<"BULLET REMAINS : "<<currentBullet;
        isShooting = true;
        Bullet *bulletShot = new Bullet(5, angle, this->x(), this->y());
        scene()->addItem(bulletShot);
        QPointF offset(30, 0);
        bulletShot->setPos(scenePos() + offset);
        timer.singleShot(attackSpeed/maxBullet, this, &RangedWeapon::ResetShootState);
    }
    else if (currentBullet <= 0)
    {
        Reload();
        qDebug()<<"RELOADING U BITCCHHHHHH";
    }
}

void RangedWeapon::Reload()
{
    if(!isReloading)
    {
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
    isReloading = false;
}
