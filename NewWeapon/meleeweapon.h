#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "weapon.h"
#include "qpropertyanimation.h"
#include "qsequentialanimationgroup.h"
#include "character.h"

class MeleeWeapon : public Weapon
{
public:
    MeleeWeapon(int attack, QGraphicsItem *parent, int attackRange, int attackSpeed, QString image = ":knife");
    void virtual Attack() override;
signals:
    void EndAttackAnimation();
private:
    void InitializeAttackAnimation();
    void OnAttack();
    void ResetAttack();
    QSequentialAnimationGroup attackAnimation;
    bool isAttack = false;
    int attackSpeed = 500;
    int attackRange = 25;
};

#endif // MELEEWEAPON_H
