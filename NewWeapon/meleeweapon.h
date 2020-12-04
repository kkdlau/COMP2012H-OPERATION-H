#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "weapon.h"
#include "qpropertyanimation.h"

class MeleeWeapon : public Weapon
{
public:
    /**
     * @brief MeleeWeapon constructor
     * @param attack to set the attack damage of the knife
     * @param attackRange to set how far does the knife attack
     * @param attackSpeed to set the duration of the animation played
     * @param parent to set the QGraphicsitem parent of MeleeWeapon
     * @param image to set the image of the weapon
     */
    MeleeWeapon(int attack,  int attackRange, int attackSpeed,QGraphicsItem *parent = nullptr, QString image = ":knife");
    /**
     * @brief Attack implementation for MeleeWeapon
     * @param angle - not used
     */
    void virtual Attack(int angle) override;
//    void Charge();
//    void Skill();
    /**
     * @brief WeaponDataText implementation for MeleeWeapon
     * @return QString for ItemFrame QLabel
     */
    QString virtual WeaponDataText() override;
    /**
     * @brief OffsetWeaponGround implementation for MeleeWeapon offset when placed on ground
     */
    void virtual OffsetWeaponGround() override;
    /**
     * @brief OffsetWeaponPickUp implementation for MeleeWeapon offset when picked up
     */
    void virtual OffsetWeaponPickUp() override;
signals:
    /**
     * @brief EndAttackAnimation provides a signal for which an animation Attack ends
     */
    void EndAttackAnimation();
private:
    /**
     * @brief InitializeAttackAnimation implementation for MeleWeapon attack animation
     */
    virtual void InitializeAttackAnimation() override;
    /**
     * @brief OnAttack function as a placeholder on what the MeleeWeapon should do when attacking
     */
    void OnAttack();
    /**
     * @brief ResetAttack is a function to reset the isAttack
     */
    void ResetAttack();
    /**
     * @brief isAttack sets attack state
     */
    bool isAttack = false;
    /**
     * @brief isAttackAnimation sets if attack animation has run
     */
    bool isAttackAnimation = false;
    /**
     * @brief attackSpeed sets how fast the animation
     */
    int attackSpeed = 500;
    /**
     * @brief attackRange how far does the animation travel
     */
    int attackRange = 25;
};

#endif // MELEEWEAPON_H
