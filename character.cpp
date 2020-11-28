#include "character.h"
#include <QDebug>
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

bool testCollidesWithItem(QGraphicsItem* head, QGraphicsItem* obj) {
    bool collide = head->collidesWithItem(obj);
    if (collide) {
        return (QVector2D{head->pos() - obj->pos()}).length() >= 0.01;
    } else return false;
}

void Character::moveBy(qreal x, qreal y) {
   bool intersect = head->boundingRect().intersects(presetMap->test_obstacle->boundingRect());

   animation = new QPropertyAnimation(this, "move");
   animation->keyValueAt(0.01);
   animation->setDuration(100);
   animation->setStartValue(this->getPosition());
   animation->setEndValue(this->pos() + QPoint(x, y));

   if (head->collidesWithItem(presetMap->test_obstacle)) {
       const QPointF oldPoint = this->getPosition();
       animation->updateCurrentValue(0.01);
//       qDebug() << oldPoint << ", new: " << animation->update;
       this->setPosition(animation->keyValueAt(0.01).toPointF());
       if (head->collidesWithItem(presetMap->test_obstacle)) {
           this->setPosition(oldPoint);
           qDebug() << "set old";
           return;
       }
   }

   animation->start();
   connect(animation, &QPropertyAnimation::valueChanged, this, [&]() {
       if (head->collidesWithItem(presetMap->test_obstacle)) {
           animation->stop();
       }
   });
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
