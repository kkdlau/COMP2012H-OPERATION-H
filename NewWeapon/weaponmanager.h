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
    /**
     * @brief AddWeapon add Weapon* to the weaponDatabase
     */
    void AddWeapon(Weapon* weapon);
    /**
     * @brief DeleteWeapon remove Weapon* from the weaponDatabase
     * @param weapon is the Weapon* data what wants to be added
     */
    void DeleteWeapon(Weapon* weapon);
    /**
     * @brief GenerateRandomWeapon creates random weapon from the QRandomGenerator
     * @param weapon is the target Weapon* to be removed
     * @return Weapon*
     */
    Weapon* GenerateRandomWeapon();
    /**
     * @brief GetWeaponDatabase return the weaponDatabase
     * @return QList<Weapon*>
     */
    const QList<Weapon*> GetWeaponDatabase() const;
    /**
     * @brief GetWeapon get the specified
     * @param weaponId
     * @return the Weapon* with the specified weaponId
     */
    Weapon* GetWeapon(int weaponId);
    /**
     * @brief getInstance
     * @return return the WeaponManager Instance. If Instance is nullptr, a WeaponManager will be created instead
     */
    static WeaponManager* getInstance();
private:
    /**
     * @brief WeaponManager constructor
     */
    WeaponManager();
    /**
     * @brief Instance of the WeaponManager
     */
    static WeaponManager* Instance;
    /**
     * @brief weaponDatabase is a list of Weapon*
     */
    QList<Weapon*> weaponDatabase;

};

#endif // WEAPONMANAGER_H
