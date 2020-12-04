#ifndef ITEMFRAME_H
#define ITEMFRAME_H
#include "QGraphicsItemGroup"
#include <QGraphicsProxyWidget>
#include <QLabel>
#include "NewWeapon/weapon.h"
#include "GameCharacter/character.h"

class ItemFrame : public QObject, public QGraphicsItemGroup
{
public:
    ItemFrame();
    ~ItemFrame();

    /**
     * @brief ChangeWeaponPicture sets the weapon picture to picture
     * @param picture the picture to be used (we use .png)
     */
    void ChangeWeaponPicture(QPixmap picture);

    /**
     * @brief ChangeText sets the weapon stats to data
     * Also resizes the weapon label
     * @param data QString which contains the weapon stats
     */
    void ChangeText(QString data);

    /**
     * @brief SetTargetWeapon sets the target weapon to weaponData
     * Also changes the item frame picture and label
     * @param weaponData weapon to be set as target
     */
    void SetTargetWeapon(Weapon* weaponData);

    /**
     * @brief unfocusedWeapon resets the item frame
     * Also disconnects weapon signal and item frame slot
     * Performs sanity check to see if weaponData is in focus
     * @param weaponData weapon to be unfocused
     */
    void unfocusedWeapon(Weapon* weaponData);

    /**
     * @brief characterSingalSetup connects target character signlas to item frame slots
     * @param target the target character
     */
    void characterSingalSetup(Character* target);

protected:
    QGraphicsRectItem *layout;
    QGraphicsPixmapItem *weaponImage;
    QGraphicsProxyWidget *labelProxy;
    QLabel *weaponStat;
    Weapon* currentFocusedWeapon = nullptr;
};
#endif // ITEMFRAME_H
