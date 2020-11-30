#ifndef CHARACTER_H
#define CHARACTER_H
#include <QPointF>
#include <QVector2D>
#include <QPropertyAnimation>
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"
#include "NewWeapon/weapon.h"
#include "../GameMapCanvas/map.h"

class Character : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF move READ getPosition WRITE setPosition)
public:
    Character(int stepValue = 5, Map* map = nullptr);
    Character(QString, int, int stepValue = 5, Map* map = nullptr);
    Character(const QStringList, int stepValue = 5, Map* map = nullptr);
    ~Character();

    static const int WIDTH;
    static const int HEIGHT;
    static Character createTestCharacter();

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

    void setPosition(QPointF p);

    /**
     * @brief setMovementVector set character movement vector
     *
     * @param v movement vector
     */
    void setMovementVector(QVector2D v);

    void moveBy(qreal x, qreal y);

    Character operator=(const Character& input);

    //SAMPLE WEAPON TEST STEVEN
    void EquipWeapon();
    void DequipWeapon();
    //SAMPLE WEAPON TEST STEVEN

private:
    QString characterName;


    QPropertyAnimation* animation;
    QVector2D moveVector;


    QGraphicsPixmapItem* head;
    QGraphicsPixmapItem* gun; // for testing purpose
    Map* presetMap;
    int characterHealth;
    int curWeaponID;

    //SAMPLE WEAPON TEST STEVEN
    Weapon *currentWeapon = nullptr;
    //SAMPLE WEAPON TEST STEVEN


    int stepValue; // step value for height system, it describles how "high" can a character travels.

    void moveYPositive(int dy);
    void moveYNegative(int dy);

    void moveXPositive(int dx);
    void moveXNegative(int dx);

signals:
    void isMoving(Character*);
};

#endif // CHARACTER_H
