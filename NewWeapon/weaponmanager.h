#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <QObject>
#include "NewWeapon/meleeweapon.h"
#include "NewWeapon/rangedweapon.h"
class WeaponManager : public QObject
{
    Q_OBJECT
public:
    WeaponManager();
    ~WeaponManager();
    void AddWeapon(Weapon*);
    void DeleteWeapon(Weapon*);
    Weapon* GenerateRandomWeapon();
    //TEST
    const QList<Weapon*> GetWeaponDatabase() const;
    Weapon* GetWeapon(int weaponId);
    void EquipWeapon(int weaponId, QGraphicsItem* owner);
    void DequipWeapon(int weaponId);
    void AttackWeapon(int weaponId, int angle);
    //TEST
    static WeaponManager* getInstance();
    //insert preventive later
private:
    static WeaponManager* Instance;
    QList<Weapon*> weaponDatabase;

};

#endif // WEAPONMANAGER_H
