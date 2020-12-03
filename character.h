#ifndef CHARACTER_H
#define CHARACTER_H
#include <QPointF>
#include <QVector2D>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QHash>
#include "qstring.h"
#include "qstringlist.h"
#include "qgraphicsitem.h"
#include "GameScene/map.h"
#include "NewWeapon/weapon.h"
#include "UI/healthbar.h"

class Character : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal moveX READ getPositionX WRITE setPositionX)
    Q_PROPERTY(qreal moveY READ getPositionY WRITE setPositionY)
public:
    enum MOVE_DIRECTION { LEFT = 0x0001, RIGHT = 0x0002, UP = 0x0020, DOWN = 0x0040 };
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


    /*for animation - start*/

    qreal getPositionX() const;

    qreal getPositionY() const;

    void setPositionX(qreal p);

    void setPositionY(qreal p);

    /*for animation - end*/

    /**
     * @brief setMovementVector set character movement vector
     *
     * @param v movement vector
     */
    void setMovementVector(QVector2D v);

    QVector2D getMovementvector(unsigned direction);

    void moveBy(qreal x, qreal y);

    /**
     * @brief moveTo Move to center of specific grid.
     * @param x Grid coordinate x
     * @param y Grid coordinate y
     */
    void moveTo(int x, int y);

    /**
     * @brief moveTo moveTo Move to center of specific grid.
     * @param p Grid coordinate
     */
    void moveTo(QPoint p);

    Character operator=(const Character& input);

    //SAMPLE WEAPON TEST STEVEN

    void pickWeapon();
    void equipWeapon(Weapon* weapon);
    void dequipWeapon();


    void DealDamage(int damage);
    void virtual Harmed();
    //SAMPLE WEAPON TEST STEVEN

    //SAMPLE WEAPON TEST STEVEN
    Weapon* currentWeapon = nullptr;
    int characterHealth = 10;
    int maxHealth = 10;
    //SAMPLE WEAPON TEST STEVEN
    void setRotation(qreal degree);
protected:
    Map* presetMap;
private:
    float spd{10};
    QString characterName;
    QPropertyAnimation* animationX{nullptr};
    QPropertyAnimation* animationY{nullptr};
    QVector2D moveVector;


    QGraphicsPixmapItem* head;
    QGraphicsPixmapItem* gun; // for testing purpose
    HealthBar* health;
    int curWeaponID;

    bool move_state{false}; // if last moment was moving, then true, otherwise false

    int stepValue; // step value for height system, it describles how "high" can a character travels.

    void moveYPositive(int dy);
    void moveYNegative(int dy);

    void moveXPositive(int dx);
    void moveXNegative(int dx);

//    QMediaPlayer* footstep_sound{nullptr};
    QMediaPlayer footstep_sound;

signals:
    void startMoving();
    void stopMoving();
    void isMoving(QPointF p);
    void blockByObstacle(MOVE_DIRECTION);

    void equipWeaponSignal(Weapon*);
    void dequipWeaponSignal(Weapon*);
    void attackWeaponSignal(QString); //change tmrw

    void deadSignal(Character*);


public:
    class Controller {
    private:
        static QHash<char, MOVE_DIRECTION> KEY2DIRETION;
        QHash<char, bool> keyState;
        Character* toControl{nullptr};

        void keyStateInitialize();
    public:
        Controller();
        static const QVector<char> listenKeyList;
        void setState(char key, bool pressed);

        void control(Character* c);

        void updateKeyPressControl();
        void updateKeyHoldingControl();
    };
};

#endif // CHARACTER_H
