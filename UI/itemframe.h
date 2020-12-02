#ifndef ITEMFRAME_H
#define ITEMFRAME_H
#include "QGraphicsItemGroup"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include "NewWeapon/weapon.h"
#include "character.h"

class ItemFrame : public QObject, public QGraphicsItemGroup
{
public:
    ItemFrame();
    ~ItemFrame();
    void ChangeWeaponPicture(QPixmap picture);
    void ChangeText(QString data);
    void SetTargetWeapon(Weapon*);
    void unfocusedWeapon(Weapon*);
    void characterSingalSetup(Character*);
protected:
    QGraphicsRectItem *layout;
    QGraphicsPixmapItem *weaponImage;
    QGraphicsProxyWidget *labelProxy;
    QLabel *weaponStat;
    Weapon* currentFocusedWeapon = nullptr;
};
#endif // ITEMFRAME_H
