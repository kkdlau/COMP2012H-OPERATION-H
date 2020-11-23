#ifndef CHARACTER_H
#define CHARACTER_H
#include <QPointF>
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"
#include "Weapons/weapon.h"
#include "../GameMapCanvas/map.h"

class Character : public QGraphicsItemGroup
{
public:
    Character(int stepValue = 5);
    Character(QString, int, int stepValue = 5);
    Character(const QStringList, int stepValue = 5);

    static Character createTestCharacter();
    ~Character();
    QString get_name() const;
    int get_health() const;
    bool is_alive() const;
    void set_name(QString name);
    void set_health(int health);
    void shoot();

    /**
     * @brief getPosition get character position
     * @return position in floating format. You can modify the position but the changes won't reflect on the character.
     */
    QPointF getPosition() const;

    void moveBy(qreal x, qreal y);

    Character operator=(const Character& input);

private:
    QString characterName;
    Map* presetMap;
    int characterHealth;
    int curWeaponID;
    int stepValue; // step value for height system, it describles how "high" can a character travels.

signals:
    void isMoving(Character*);
};

#endif // CHARACTER_H
