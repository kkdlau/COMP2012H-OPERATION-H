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
    labelProxy->setWidget(weaponStat);
    weaponStat->setText("-/-");
    labelProxy->setPos(layout->rect().width()/2 - labelProxy->rect().width(), layout->rect().height());
    addToGroup(layout);
    addToGroup(weaponImage);
    addToGroup(labelProxy);
}

ItemFrame::~ItemFrame()
{
    delete layout;
    delete weaponImage;
    delete labelProxy;
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
    connect(currentFocusedWeapon, &Weapon::OnWeaponUpdate, this, &ItemFrame::ChangeWeaponPicture);
    ChangeWeaponPicture(currentFocusedWeapon->pixmap());
    ChangeText("currentFocusedWeapon->");
}

void ItemFrame::unfocusedWeapon()
{
    disconnect(currentFocusedWeapon, nullptr, nullptr, nullptr);
    currentFocusedWeapon = nullptr;
    ChangeWeaponPicture(QPixmap());
    ChangeText("-//-");
}
