#include "rangedweapon.h"
#include "Weapons/bullet.h"
#include "character.h"
RangedWeapon::RangedWeapon(int attack, int attackSpeed, int reloadSpeed,int maxBullet, QGraphicsItem *parent): Weapon(WeaponType::RANGED, attack,parent), attackSpeed(attackSpeed), reloadSpeed(reloadSpeed), maxBullet(maxBullet), currentBullet(maxBullet)
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
        Bullet *bulletShot = new Bullet(5, angle, this->x(), this->y(), parentItem());
        scene()->addItem(bulletShot);
        bulletShot->setPos(this->scenePos());
        timer.singleShot(attackSpeed/maxBullet, this, &RangedWeapon::ResetShootState);
        emit OnWeaponUpdate(WeaponDataText());
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
