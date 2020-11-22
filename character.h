#ifndef CHARACTER_H
#define CHARACTER_H
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"
#include "Weapons/weapon.h"

class Character : public QGraphicsItemGroup
{
public:
    Character();
    Character(QString, int);
    Character(const QStringList);

    static Character* createThirdParty();
    ~Character();
    QString get_name() const;
    int get_health() const;
    bool is_alive() const;
    void set_name(QString name);
    void set_health(int health);
    void shoot();

private:
    QString characterName;
    int characterHealth;
    int curWeaponID;
};

#endif // CHARACTER_H
