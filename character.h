#ifndef CHARACTER_H
#define CHARACTER_H
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"
#include "Weapons/weapon.h"
#include "qdebug.h"

class Character : public QGraphicsPixmapItem
{
public:
    Character();
    Character(QString, int);
    Character(const QStringList);

    static Character* createThirdParty();
    ~Character();
    QString get_name() const;
    void on_hit();
    int get_health() const;
    bool is_alive() const;
    void set_name(QString name);
    void set_health(int health);
    void shoot();
    Character operator=(const Character& input);

private:
    QString characterName;
    int characterHealth;
    int curWeaponID;
};

#endif // CHARACTER_H
