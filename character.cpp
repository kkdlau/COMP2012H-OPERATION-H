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
    setPos(QPointF{32.0f * 2 + 16, 32.0f * 3});
    health = new HealthBar(head);
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
        if (pos().y() + 16 + dy >  presetMap->getHeight(Map::UNIT::PIXEL)) {
            setY(presetMap->getHeight(Map::UNIT::PIXEL) - 16);
            emit blockByObstacle(MOVE_DIRECTION::DOWN);
            animationY->stop();
        } else {
            setY(pos().y() + dy);
        }
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
        emit blockByObstacle(MOVE_DIRECTION::DOWN);
        animationY->stop();
    } else if (lowerGrid.getHeight() && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::DOWN);
        animationY->stop();
    } else this->setY(pos().y() + dy);
}

void Character::moveYNegative(int dy) {

    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    if (p.y() == 0) {
        if (pos().y() - 16 + dy <  0) {
            setY(16);
            emit blockByObstacle(MOVE_DIRECTION::UP);
        } else {
            setY(pos().y() + dy);
        }
        return;
    }


//    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().x()) % 32;

//    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

//    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, -1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, -1}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::UP);
    } else if (lowerGrid.getHeight() && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::UP);
    } else this->setY(pos().y() + dy);
}

void Character::moveXPositive(int dx) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    if (p.x() == presetMap->getWidth(Map::UNIT::GRID) - 1) {
        if (pos().x() + 16 + dx >  presetMap->getWidth(Map::UNIT::PIXEL)) {
            setX(presetMap->getWidth(Map::UNIT::PIXEL) - 16);
            animationX->stop();
            emit blockByObstacle(MOVE_DIRECTION::RIGHT);
        } else {
            setX(pos().x() + dx);
        }

        return;
    }

//    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().y()) % 32;

//    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

//    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{1, shiftIndex}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::RIGHT);
        animationX->stop();
    } else if (lowerGrid.getHeight() && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::RIGHT);
        animationX->stop();
    } else this->setX(pos().x() + dx);
}

void Character::moveXNegative(int dx) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    if (p.x() == 0) {
        if (pos().x() - 16 + dx < 0) {
            setX(16); animationX->stop();
            emit blockByObstacle(MOVE_DIRECTION::LEFT);
        } else {
            setX(pos().x() + dx);
        }
        return;
    }

//    qDebug() <<"x: " << pos().x();
    int shift = qFloor(pos().y()) % 32;

//    qDebug() << "shift: " << shift;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

//    qDebug() << "shiftIndex: " << shiftIndex;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{-1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{-1, shiftIndex}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2.getHeight() && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::LEFT);
        animationX->stop();
    } else if (lowerGrid.getHeight() && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::LEFT);
        this->animationX->stop();
    } else this->setX(pos().x() + dx);
}

void Character::moveBy(qreal x, qreal y) {
//   bool intersect = head->boundingRect().intersects(presetMap->test_obstacle->boundingRect());

if (x) {
    if (animationX) animationX->stop();
    delete animationX;
    animationX = new QPropertyAnimation(this, "moveX");
    animationX->setDuration(70);
    animationX->setStartValue(this->getPositionX());
    animationX->setEndValue(this->getPositionX() + x);
    animationX->start();
}

if (y) {
    if (animationY) animationY->stop();
    delete animationY;
    animationY = new QPropertyAnimation(this, "moveY");
    animationY->setDuration(70);
    animationY->setStartValue(this->getPositionY());
    animationY->setEndValue(this->getPositionY() + y);
    animationY->start();
}

}

qreal Character::getPositionX() const {
    return pos().x();
}

qreal Character::getPositionY() const {
    return pos().y();
}

void Character::setPositionX(qreal p) {
    const qreal diff = p - pos().x();
    if (diff > 0) {
        moveXPositive(diff);
    } else {
        moveXNegative(diff);
    }

    emit isMoving(this->pos());
}

void Character::setPositionY(qreal p) {
    const qreal diff = p - pos().y();
    if (diff > 0) {
        moveYPositive(diff);
    } else {
        moveYNegative(diff);
    }

     emit isMoving(this->pos());
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
    if(currentWeapon != nullptr)
    {
        currentWeapon->Attack(this->rotation());
    }
}

void Character::EquipWeapon()
{

    QPoint gridLocation = (this->scenePos()/ 32).toPoint();
    GridInfo &found = presetMap[0][gridLocation.y()-1][gridLocation.x() - 1];
    qDebug()<<"Grid Found, Checking "<<gridLocation.y()-1<<"/"<<gridLocation.x() -1<<"//"<<found.GetPosition();
    if(found.IsWeaponInGrid())
    {
        qDebug()<<"FOUND WEAPON AH";
        Weapon* getWeapon = found.GetWeaponData();
        if(currentWeapon != nullptr)
        {
            found.AddWeaponToGrid(currentWeapon);
            currentWeapon->Unequip();
        }
        getWeapon->Equip(gun);
        currentWeapon = getWeapon;
        if(weaponUI != nullptr)
        {
            weaponUI->SetTargetWeapon(getWeapon);
        }
        return;
    }
    if(currentWeapon != nullptr)
    {
        DequipWeapon();
    }

//    QList<QGraphicsItem*> collide = collidingItems();

//    for(int i = 0; i < collide.length(); i++)
//    {
//        Weapon *data = dynamic_cast<Weapon*>(collide[i]);
//        if(data && data != currentWeapon)
//        {
//            if(currentWeapon != nullptr)
//            {
//                DequipWeapon();
//            }
//            data->Equip(gun);
//            currentWeapon = data;
//            if(weaponUI != nullptr)
//            {
//                weaponUI->SetTargetWeapon(data);
//            }
//            return;
//        }
//    }
//    if(currentWeapon != nullptr)
//    {
//        DequipWeapon();
//    }
}

void Character::DequipWeapon()
{
    currentWeapon->Unequip();
    QPoint gridLocation = (this->scenePos()/ 32).toPoint();
    GridInfo &found = presetMap[0][gridLocation.y()-1][gridLocation.x() - 1];
    found.AddWeaponToGrid(currentWeapon);
    currentWeapon= nullptr;
    weaponUI->unfocusedWeapon();
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
