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
#include "UI/healthbar.h"

class Weapon;
class Map;

enum charType
{
    PLAYER,ENEMY
};

class Character : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal moveX READ getPositionX WRITE setPositionX)
    Q_PROPERTY(qreal moveY READ getPositionY WRITE setPositionY)
public:
    /**
     * @brief The MOVE_DIRECTION enum
     *
     * The direction allows you to describle the direction easily with "|" operator.
     *
     * Example: LEFT + UP = LEFT | UP
     */
    enum MOVE_DIRECTION { LEFT = 0x0001, RIGHT = 0x0002, UP = 0x0020, DOWN = 0x0040 };

    Character(charType charType = charType::PLAYER, int stepValue = 5, Map* map = nullptr);
    Character(QString, int, int stepValue = 5, Map* map = nullptr);
    Character(const QStringList, int stepValue = 5, Map* map = nullptr);
    ~Character();

    static const int WIDTH;
    static const int HEIGHT;

    int get_health() const;
    bool is_alive() const;
    void set_health(int health);
    void attack();

    QPoint getGridPos() const;

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

    /**
     * @brief setGridPos Set Character position
     * @param p Position in GRID positioning system
     */
    void setGridPos(QPoint p);

    Character operator=(const Character& input);

    //SAMPLE WEAPON TEST STEVEN

    void pickWeapon();
    void equipWeapon(Weapon* weapon);
    void dequipWeapon();


    void DealDamage(int damage);
    void virtual Harmed();

    charType getCharacterType();

    Weapon* currentWeapon = nullptr;
    int characterHealth = 10;
    int maxHealth = 10;
    void setRotation(qreal degree);

    bool isPerfectCenterize() const;
protected:
    Map* presetMap;
    charType typeOfCharacter;
private:
    float spd{10};
    QString characterName;
    QPropertyAnimation* animationX{nullptr};
    QPropertyAnimation* animationY{nullptr};
    QVector2D moveVector;
    QPoint aimPos;


    QGraphicsPixmapItem* head;
    QGraphicsPixmapItem* gun; // for testing purpose
    HealthBar* healthBar;
    int curWeaponID;

    int stepValue; // step value for height system, it describles how "high" can a character travels.

    /**
     * @brief moveYPositive Move the character along positive y-axis.
     * @param dy The pixel to move along y-axis, should be a positive value.
     */
    void moveYPositive(int dy);

    /**
     * @brief moveYNegative Move the character along negative y-axis.
     * @param dy The pixel to move along y-axis, should be a negative value.
     */
    void moveYNegative(int dy);

    /**
     * @brief moveXPositive Move the character along positive x-axis.
     * @param dx The pixel to move along x-axis, should be a positive value.
     */
    void moveXPositive(int dx);

    /**
     * @brief moveXNegative Move the character along negative x-axis.
     * @param dx The pixel to move along x-axis, should be a negative value.
     */
    void moveXNegative(int dx);

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
    /**
     * @brief The Controller class
     *
     * This class is designed for the character who is controlled by the user.
     *
     * It takes the control of the character, and also manages the state of keys.
     *
     * Once the listening keys' state is updated, the controller will control according to the state.
     */
    class Controller {
    private:
        static QHash<char, MOVE_DIRECTION> KEY2DIRETION; // variable for mapping key to character movement direction
        QHash<char, bool> keyState; // internal key state. TRUE = pressed, FALSE = released
        Character* toControl{nullptr}; // by default, controller takes the control of no character.

        /**
         * @brief keyStateInitialize Initialize key states. Only keys which need to listen are initialized.
         */
        void keyStateInitialize();
    public:
        Controller();
        Controller(const Controller&) = delete;

        enum KeyState {RELEASED = false, PRESSED = true};


        static const QVector<char> listenKeyList; // list for storing all keys which need to listen.

        /**
         * @brief setState Set the state of key.
         * @param key Key Code
         * @param state The state of that key, should be either PRESSED or RELEASE.
         */
        void setState(char key, KeyState state);

        /**
         * @brief unControl Stop controlling subsribled character.
         */
        void unControl();

        /**
         * @brief control Takes the control of character
         * @param c Character to control
         */
        void control(Character* c);

        /**
         * @brief updateKeyPressControl Update control based on current key pressed state.
         */
        void updateKeyPressControl();

        /**
         * @brief updateKeyHoldingControl Update control based on current key holding state.
         */
        void updateKeyHoldingControl();
    };
};

#include "NewWeapon/weapon.h"
#include "GameScene/map.h"

#endif // CHARACTER_H
