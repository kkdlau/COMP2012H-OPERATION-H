#include "weaponmanager.h"
#include "qdebug.h"
#include "UI/itemframe.h"

WeaponManager* WeaponManager::Instance = nullptr;

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager(){
    qDebug()<<"SINCE IT FUKIN ACCESSED IT IT MEANS ITS DELETED";
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
    weaponDatabase.append(tempWeapon);
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
        ChangeWeaponPicture(targetWeapon->pixmap());
        if(targetWeapon->GetWeaponType() == WeaponType::RANGED)
        {
            RangedWeapon* weapon = dynamic_cast<RangedWeapon*>(targetWeapon);
            ChangeText(weapon->ReturnAmmoString());
        }
        else
        {
            ChangeText("-//-");
        }

    }
}

void WeaponManager::AttackWeapon(int weaponId, int angle)
{
    Weapon* targetWeapon = GetWeapon(weaponId);
    if(targetWeapon != nullptr)
    {
        targetWeapon->Attack(angle);
    }
    if(targetWeapon->GetWeaponType() == WeaponType::RANGED)
    {
        RangedWeapon* weapon = dynamic_cast<RangedWeapon*>(targetWeapon);
        ChangeText(weapon->ReturnAmmoString());
    }
    else
    {
        ChangeText("-//-");
    }
}

void WeaponManager::DequipWeapon(int weaponId)
{
    Weapon* targetWeapon = GetWeapon(weaponId);
    if(targetWeapon != nullptr)
    {
        targetWeapon->Unequip();
        ChangeWeaponPicture(QPixmap());
        ChangeText("-//-");
    }
}
