#include "weaponmanager.h"
#include "qdebug.h"
WeaponManager* WeaponManager::Instance = nullptr;

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager(){

}
WeaponManager* WeaponManager::getInstance()
{
    if(Instance == nullptr)
    {
        Instance = new WeaponManager();
    }
    return Instance;
}

void WeaponManager::AddWeapon(Weapon * weaponData)
{
    weaponDatabase.append(weaponData);
    qDebug()<<"INSERTING WEAPON ID WITH CODE "<<weaponData->GetWeaponId();
}

void WeaponManager::DeleteWeapon(Weapon* weaponData)
{
    if(weaponDatabase.contains(weaponData))
    {
        weaponDatabase.removeOne(weaponData);
    }
}

Weapon* WeaponManager::GenerateRandomWeapon()
{
    int number = QRandomGenerator::global()->generate()% 2;
    Weapon* tempWeapon;
    if(number == 1)
    {
        tempWeapon = new MeleeWeapon(10,50,500);
    }
    else
    {
        tempWeapon =  new RangedWeapon(5,500,500,10);
    }
    return tempWeapon;
}

const QList<Weapon*> WeaponManager::GetWeaponDatabase() const
{
    return weaponDatabase;
}

Weapon* WeaponManager::GetWeapon(int weaponId)
{
    for(int i = 0; i < weaponDatabase.length(); i++)
    {
        qDebug()<<"WEAPON LOOKING: "<<weaponDatabase[i]->GetWeaponId();
        if(weaponDatabase[i]->GetWeaponId() == weaponId)
        {
            qDebug()<<"WEAPON FOUND BABY";
            return weaponDatabase[i];
        }
    }
    return nullptr;
}

void WeaponManager::EquipWeapon(int weaponId, QGraphicsItem *owner)
{
     qDebug()<<"EQUIP FOUND BABY";
    Weapon* targetWeapon = GetWeapon(weaponId);
    if(targetWeapon != nullptr)
    {
        qDebug()<<"EQUIPping BABY";
        targetWeapon->Equip(owner);
    }
}

void WeaponManager::AttackWeapon(int weaponId, int angle)
{
    Weapon* targetWeapon = GetWeapon(weaponId);
    if(targetWeapon != nullptr)
    {
        targetWeapon->Attack(angle);
    }
}
