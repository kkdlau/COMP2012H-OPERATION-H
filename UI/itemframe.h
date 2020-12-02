#ifndef ITEMFRAME_H
#define ITEMFRAME_H
#include "QGraphicsItemGroup"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include "NewWeapon/weapon.h"

class ItemFrame : public QObject, public QGraphicsItemGroup
{
public:
    ItemFrame();
    ~ItemFrame();
    void ChangeWeaponPicture(QPixmap picture);
    void ChangeText(QString data);
    void SetTargetWeapon(Weapon*);
    void unfocusedWeapon();
protected:
    QGraphicsRectItem *layout;
    QGraphicsPixmapItem *weaponImage;
    QGraphicsProxyWidget *labelProxy;
    QLabel *weaponStat;
    Weapon* currentFocusedWeapon = nullptr;
};
#endif // ITEMFRAME_H
