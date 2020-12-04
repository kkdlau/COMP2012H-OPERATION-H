#include "weaponmanager.h"
#include "qdebug.h"
#include "UI/itemframe.h"

WeaponManager* WeaponManager::Instance = nullptr;

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager(){
    for(int i = 0; i < weaponDatabase.length(); i++)
    {
        delete weaponDatabase[i];
    }
    Instance = nullptr; //TODO ID FUCKIN KNOW
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
//    int number = QRandomGenerator::global()->generate()% 2;
    int number = 1;
    Weapon* tempWeapon;
    if(number == 0)
    {
        tempWeapon = new MeleeWeapon(20,50,500);
    }
    else
    {
        tempWeapon =  new RangedWeapon(20,500,500,10);
    }
    AddWeapon(tempWeapon);
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


