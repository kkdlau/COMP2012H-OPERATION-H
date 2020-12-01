#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "weapon.h"
#include "qpropertyanimation.h"
#include "qsequentialanimationgroup.h"

class MeleeWeapon : public Weapon
{
public:
    MeleeWeapon(int attack,  int attackRange, int attackSpeed,QGraphicsItem *parent = nullptr, QString image = ":knife");
    void virtual Attack(int angle) override;
    void Charge();
    void Skill();
signals:
    void EndAttackAnimation();
private:
    void InitializeAttackAnimation();
    void OnAttack();
    void ResetAttack();
    void ResetCharge();
    QSequentialAnimationGroup attackAnimation;
    bool isAttack = false;
    bool isAttackAnimation = false;
    bool isCharged = false;
    int attackSpeed = 500;
    int attackRange = 25;
    int chargeTime = 1000;
    int skillTime = 5000;
    int skillCooldown = 15000;
};

#endif // MELEEWEAPON_H
