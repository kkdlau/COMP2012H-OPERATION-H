#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <QObject>
#include "NewWeapon/meleeweapon.h"
#include "NewWeapon/rangedweapon.h"
class WeaponManager : public QObject
{
    Q_OBJECT
public:

    ~WeaponManager();
    void AddWeapon(Weapon*);
    void DeleteWeapon(Weapon*);
    Weapon* GenerateRandomWeapon();
    const QList<Weapon*> GetWeaponDatabase() const;
    Weapon* GetWeapon(int weaponId);
    static WeaponManager* getInstance();
private:
        WeaponManager();
    static WeaponManager* Instance;
    QList<Weapon*> weaponDatabase;

};

#endif // WEAPONMANAGER_H
