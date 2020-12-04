#include "itemframe.h"
#include "QBrush"

ItemFrame::ItemFrame()
{
    layout = new QGraphicsRectItem();
    layout->setRect(0,0,32,32);
    layout->setBrush(QBrush(Qt::red));
    labelProxy = new QGraphicsProxyWidget();
    weaponStat = new QLabel();
    weaponImage = new QGraphicsPixmapItem();
    weaponImage->setPos(0, layout->rect().height()/2);
    weaponStat->setText("-/-");
    weaponStat->setMinimumWidth(32);
    labelProxy->setWidget(weaponStat);
    labelProxy->setPos(2, layout->rect().height());
    addToGroup(layout);
    addToGroup(weaponImage);
    addToGroup(labelProxy);
}

ItemFrame::~ItemFrame()
{
    delete layout;
    if(currentFocusedWeapon != nullptr)
    {
        unfocusedWeapon(currentFocusedWeapon);
    }
    delete weaponImage;
    delete labelProxy;
//    delete weaponStat;
}

void ItemFrame::ChangeText(QString data)
{
    weaponStat->setText(data);
    labelProxy->resize(weaponStat->size());
}

void ItemFrame::ChangeWeaponPicture(QPixmap picture)
{
    weaponImage->setPixmap(picture);
}

void ItemFrame::SetTargetWeapon(Weapon *weaponData)
{
    currentFocusedWeapon = weaponData;
    ChangeWeaponPicture(currentFocusedWeapon->pixmap());
    ChangeText(weaponData->WeaponDataText());
}

void ItemFrame::unfocusedWeapon(Weapon* weaponData)
{
    if(weaponData == currentFocusedWeapon)
    {
        disconnect(currentFocusedWeapon, &Weapon::OnWeaponUpdate, this, &ItemFrame::ChangeWeaponPicture);
        currentFocusedWeapon = nullptr;
        ChangeWeaponPicture(QPixmap());
        ChangeText("-//-");
    }

}

void ItemFrame::characterSingalSetup(Character *target)
{
    connect(target, &Character::equipWeaponSignal, this, &ItemFrame::SetTargetWeapon);
    connect(target, &Character::dequipWeaponSignal, this, &ItemFrame::unfocusedWeapon);
    connect(target, &Character::attackWeaponSignal, this, &ItemFrame::ChangeText);
}
