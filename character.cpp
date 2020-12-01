#include "character.h"
#include <QDebug>
#include <QtMath>
#include <QVector2D>

/*static Character member definitation*/
const int Character::WIDTH = Map::GRID_SIZE_W;
const int Character::HEIGHT = Map::GRID_SIZE_H;

Character::Character(QString name, int health, int stepValue, Map* map) : characterName(name), characterHealth(health), stepValue{stepValue}, presetMap{map}
{

}

Character::Character(const QStringList data, int stepValue, Map* map): stepValue{stepValue}, presetMap{map}
{

}

Character::Character(int stepValue, Map* map): stepValue{stepValue}, presetMap{map} {
    head = new QGraphicsPixmapItem(QPixmap(":character_test"));
    head->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    head->setOffset(QPointF(-Character::WIDTH / 2, -Character::HEIGHT / 2));
    gun = new QGraphicsPixmapItem();
    addToGroup(head);
    addToGroup(gun);
    setPos(QPointF{32 * 3, 32.0f * 7});
    weaponManager = WeaponManager::getInstance();
    
}

QPointF Character::getPosition() const {
    return pos();
}

void Character::setMovementVector(QVector2D v) {
    moveVector = v;
}

void Character::setPosition(QPointF p) {
    setPos(p);
}

void Character::moveYPositive(int dy) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    if (p.y() == presetMap->getHeight(Map::UNIT::GRID) - 1) {
        setY(pos().y() + 16 + dy >  presetMap->getHeight(Map::UNIT::PIXEL)? presetMap->getHeight(Map::UNIT::PIXEL) - 16: pos().y() + dy);
        return;
    }

//    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().x()) % 32;

//    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

//    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, 1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, 1}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
    } else if (lowerGrid.getHeight() && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
    } else this->setY(pos().y() + dy);
}

void Character::moveYNegative(int dy) {
    if (pos().y() - 16.0 + dy < 0) {
        pos().ry() = 16.0;
        return;
    }
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().x()) % 32;

    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, -1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, -1}];

    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
    } else if (lowerGrid.getHeight() && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
    } else this->setY(pos().y() + dy);
}

void Character::moveXPositive(int dx) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().y()) % 32;

    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{1, shiftIndex}];

    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
    } else if (lowerGrid.getHeight() && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
    } else this->setX(pos().x() + dx);
}

void Character::moveXNegative(int dx) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().y()) % 32;

    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{-1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{-1, shiftIndex}];

    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
    } else if (lowerGrid.getHeight() && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
    } else this->setX(pos().x() + dx);
}

void Character::moveBy(qreal x, qreal y) {
//   bool intersect = head->boundingRect().intersects(presetMap->test_obstacle->boundingRect());

//   animation = new QPropertyAnimation(this, "move");
//   animation->keyValueAt(0.01);
//   animation->setDuration(100);
//   animation->setStartValue(this->getPosition());
//   animation->setEndValue(this->pos() + QPoint(x, y));

//   animation->start();
//   connect(animation, &QPropertyAnimation::valueChanged, this, [&]() {
//       if (head->collidesWithItem(presetMap->test_obstacle)) {
//           animation->stop();
//       }
//   });
//if (x > 0) moveXPositive(x); else moveXNegative(x);sss
if (y > 0) moveYPositive(y); else moveYNegative(y);
}



Character::~Character(){};


QString Character::get_name() const
{
    return characterName;
}

int Character::get_health() const
{
    return characterHealth;
}

void Character::set_name(QString name) {
    characterName = name;
}

void Character::set_health(int health) {
    characterHealth = health;
}

bool Character::is_alive() const{
    return characterHealth > 0;
}

void Character::shoot() {
    if(currentWeaponId != -1)
    {
        weaponManager->AttackWeapon(currentWeaponId, 45);
    }
}

void Character::EquipWeapon()
{
    QList<QGraphicsItem*> collide = collidingItems();

    for(int i = 0; i < collide.length(); i++)
    {
        Weapon *data = dynamic_cast<Weapon*>(collide[i]);
        if(data)
        {
            int weaponId = data->GetWeaponId();
            qDebug()<<"GET WEAPON ID :"<<weaponId;
            Weapon* test = weaponManager->GetWeapon(weaponId);
            if(test && weaponId != currentWeaponId)
            {
                if(currentWeaponId != -1)
                {
                    DequipWeapon();
                }
                weaponManager->EquipWeapon(weaponId, gun);
                currentWeaponId = weaponId;
                return;
            }

        }
    }
}

void Character::DequipWeapon()
{
    weaponManager->DequipWeapon(currentWeaponId);
    currentWeaponId = -1;
}

void Character::DealDamage(int damage)
{
    qDebug()<<"NPPPPPP";
    characterHealth -= damage;
    Harmed();
}

void Character::Harmed()
{
    qDebug()<<"THE CURRENT HEALTH IS "<< characterHealth;
}
