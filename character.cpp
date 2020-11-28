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
    addToGroup(head);
    setPos(QPointF{16, 16});

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

void Character::collidingInY(int dy) {
    QPoint p{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};

    int shift = qFloor(pos().x()) % 32;
    int shiftIndex = shift ==  16? 0 : shift > 16? 1 : -1;

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, 1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, 1}];

    if (lowerGrid.getHeight() && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
    } else this->setY(pos().y() + dy);
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

//this->setPosition(QPointF{this->getPosition().x() + x, this->getPosition().y() + y});
    collidingInY(y);
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
//    if (curWeapon.getWeaponType()) {
//        return;
//    }
}
