#include "character.h"
#include <QDebug>
#include <QtMath>
#include <QVector2D>

/*static Character member definition*/

const int Character::WIDTH = Map::GRID_SIZE_W;
const int Character::HEIGHT = Map::GRID_SIZE_H;

Character::Character(charType charType, int stepValue, Map* map): typeOfCharacter(charType), stepValue{stepValue}, presetMap{map}, aimPos{-1, -1} {
    head = new QGraphicsPixmapItem(QPixmap(":character_test"));
    head->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    head->setOffset(QPointF(-Character::WIDTH / 2, -Character::HEIGHT / 2));
    gun = new QGraphicsPixmapItem();
    addToGroup(head);
    addToGroup(gun);
    setPos(QPointF{32* 3 + 16, 32 * 8 + 16});
    healthBar = new HealthBar(head, characterHealth, maxHealth);
    setRotation(0);

    if (typeOfCharacter == PLAYER) {
        footstep_sound.setMedia(QUrl("qrc:/footsteps_new.wav"));
        footstep_sound.setVolume(30);
        sword_sound.setMedia(QUrl("qrc:/sword.wav"));
        sword_sound.setVolume(30);
        gunshot_sound.setMedia(QUrl("qrc:/gunshot.wav"));
        gunshot_sound.setVolume(30);
    }
}

Character::~Character()
{
    delete head;
    if(currentWeapon != nullptr)
    {
        dequipWeapon();
    }
    delete gun;
    if (animationX) {
        animationX->stop();
    }
    delete animationX;
    if (animationY) {
        animationY->stop();
    }
    delete animationY;
}

QPoint Character::getGridPos() const {
    return QPoint{qFloor(pos().x() / 32.0), qFloor(pos().y() / 32.0)};
}
void Character::setMovementVector(QVector2D v) {
    moveVector = v;
}

void Character::moveYPositive(int dy) {
    QPoint p = getGridPos();

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
if (presetMap->isOutOfMap(getGridPos())) return;
    const GridInfo& grid = (*presetMap)[getGridPos()];

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, 1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, 1}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2 - grid > stepValue && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::DOWN);
        animationY->stop();
    } else if (lowerGrid - grid > stepValue && pos().y() + 16 + dy > (p.y() + 1) * 32) {
        this->setY((p.y() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::DOWN);
        animationY->stop();
    } else this->setY(pos().y() + dy);
}

void Character::moveYNegative(int dy) {

    QPoint p = getGridPos();

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
if (presetMap->isOutOfMap(getGridPos())) return;
    const GridInfo& grid = (*presetMap)[getGridPos()];

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{0, -1}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{shiftIndex, -1}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2 - grid > stepValue  && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::UP);
    } else if (lowerGrid - grid > stepValue && pos().y() - 16 + dy < p.y() * 32) {
        this->setY((p.y()) * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::UP);
    } else this->setY(pos().y() + dy);
}

void Character::moveXPositive(int dx) {
    QPoint p = getGridPos();

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

    if (presetMap->isOutOfMap(getGridPos())) return;
    const GridInfo& grid = (*presetMap)[getGridPos()];

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{1, shiftIndex}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2 - grid > stepValue && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::RIGHT);
        animationX->stop();
    } else if (lowerGrid - grid > stepValue && pos().x() + 16 + dx > (p.x() + 1) * 32) {
        this->setX((p.x() + 1) * 32 - 16);
        emit blockByObstacle(MOVE_DIRECTION::RIGHT);
        animationX->stop();
    } else this->setX(pos().x() + dx);
}

void Character::moveXNegative(int dx) {
    QPoint p = getGridPos();

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
if (presetMap->isOutOfMap(getGridPos())) return;
    const GridInfo& grid = (*presetMap)[getGridPos()];

    const GridInfo& lowerGrid = (*presetMap)[p + QPoint{-1, 0}];
    const GridInfo& lowerGrid2 = (*presetMap)[p + QPoint{-1, shiftIndex}];

//    qDebug() << "lowerGrid: " << lowerGrid.toString() << ", lowerGrid2: " << lowerGrid2.toString();

    if (lowerGrid2 - grid > stepValue && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::LEFT);
        animationX->stop();
    } else if (lowerGrid - grid > stepValue && pos().x() - 16 + dx < p.x() * 32) {
        this->setX(p.x() * 32 + 16);
        emit blockByObstacle(MOVE_DIRECTION::LEFT);
        this->animationX->stop();
    } else this->setX(pos().x() + dx);
}

void Character::moveBy(qreal x, qreal y) {
    if (!is_alive()) return;
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

    if ((footstep_sound.state() != QMediaPlayer::State::PlayingState) && (typeOfCharacter == PLAYER)) {
        footstep_sound.play();
    }
}


QVector2D Character::getMovementvector(unsigned direction) {
    switch (direction) {
    case MOVE_DIRECTION::LEFT: return QVector2D{-spd, 0};
    case MOVE_DIRECTION::RIGHT: return QVector2D{spd, 0};
    case MOVE_DIRECTION::DOWN: return QVector2D{0, spd};
    case MOVE_DIRECTION::UP: return QVector2D{0, -spd};
    case (MOVE_DIRECTION::LEFT | MOVE_DIRECTION::UP): return QVector2D{float(-spd / M_SQRT2), float(-spd / M_SQRT2)};
    case (MOVE_DIRECTION::LEFT | MOVE_DIRECTION::DOWN): return QVector2D{float(-spd / M_SQRT2), float(spd / M_SQRT2)};
    case (MOVE_DIRECTION::RIGHT | MOVE_DIRECTION::UP): return QVector2D{float(spd / M_SQRT2), float(-spd / M_SQRT2)};
    case (MOVE_DIRECTION::RIGHT | MOVE_DIRECTION::DOWN): return QVector2D{float(spd / M_SQRT2), float(spd / M_SQRT2)};
    };

    return QVector2D{};
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
    } else if (diff < 0){
        moveXNegative(diff);
    }

    if (aimPos.x() != -1) {
        float realX = aimPos.x() * 32 + 16;
        if (qAbs(realX - pos().x()) < 2) {
            setX(realX);
            animationX->stop();

            aimPos.rx() = -1;
        }
    }

    emit isMoving(this->pos());
}

void Character::setPositionY(qreal p) {
    const qreal diff = p - pos().y();
    if (diff > 0) {
        moveYPositive(diff);
    } else if (diff < 0){
        moveYNegative(diff);
    }

    if (aimPos.y() != -1) {
        float realY = aimPos.y() * 32 + 16;
        if (qAbs(realY - pos().y()) < 2) {
            setY(realY);
            animationY->stop();
            aimPos.ry() = -1;
        }
    }

     emit isMoving(this->pos());
}

void Character::moveTo(int x, int y) {
    if (!is_alive()) return;
    QPoint tmp = QPoint{x, y};
    if (presetMap->isOutOfMap(tmp)) {
        stop();
        return;
    }
    QPoint aimPosReal = QPoint{x * 32 + 16, y * 32 + 16};
    QPoint diff = getGridPos() - tmp;

    if (qAbs(diff.x()) > 1 || qAbs(diff.y()) > 1) {
        aimPos = {-1, -1};
        return; // do nothing if the given position is not a neighbor grid
    }

    unsigned direction = 0;
    aimPos = tmp;
    QPoint diffReal = aimPosReal - pos().toPoint();
    if (diffReal.x() > 0) direction |= MOVE_DIRECTION::RIGHT;
    if (diffReal.x() < 0) direction |= MOVE_DIRECTION::LEFT;
    if (diffReal.y() > 0) direction |= MOVE_DIRECTION::DOWN;
    if (diffReal.y() < 0) direction |= MOVE_DIRECTION::UP;

    QVector2D v = getMovementvector(direction);
    moveBy(v.x(), v.y());
}

void Character::moveTo(QPoint p) {
    if (!is_alive()) return;
    moveTo(p.x(), p.y());
}

int Character::get_health() const
{
    return characterHealth;
}


void Character::set_health(int health) {
    characterHealth = health;
}

bool Character::is_alive() const {
    return characterHealth > 0;
}

void Character::attack() {
    if(currentWeapon != nullptr)
    {
        attackWeaponSignal(currentWeapon->WeaponDataText());
        currentWeapon->Attack(this->rotation());
        if (currentWeapon->GetWeaponType() == WeaponType::MELEE) {
            sword_sound.play();
        }
        if (currentWeapon->GetWeaponType() == WeaponType::RANGED) {
            gunshot_sound.play();
        }
    }
}

void Character::pickWeapon() {

    qDebug() << "current pos: " << (pos() / 32).toPoint();

    QPoint currentPos = (pos() / 32).toPoint();
    currentPos.rx()--;
    currentPos.ry()--;
    GridInfo& currentGrid = (*presetMap)[currentPos];

    qDebug() << currentGrid.toString();

    if (currentGrid.isWeaponOnGround()) {
        Weapon* pickedWeapon = currentGrid.popWeapon();
        equipWeapon(pickedWeapon);

    } else if (currentWeapon != nullptr)
        dequipWeapon();
}

void Character::equipWeapon(Weapon* weapon) {
    if(currentWeapon!= nullptr)
    {
        dequipWeapon();
    }
    currentWeapon = weapon;
    addToGroup(weapon);
    weapon->SetOwner(this);
    qDebug()<<"rotation :"<<rotation();
    weapon->resetTransform();
    weapon->setPos(0,0);
    weapon->OffsetWeaponPickUp();
//    weapon->setRotation(rotation());
    qDebug()<<"rotation weapon:"<<weapon->rotation();
    emit equipWeaponSignal(currentWeapon);
}

void Character::dequipWeapon()
{
    if (currentWeapon == nullptr) return;
    QPoint currentPos = (pos() / 32).toPoint();
    currentPos.rx()--;
    currentPos.ry()--;
    GridInfo& currentGrid = (*presetMap)[currentPos];
    currentWeapon->SetOwner(nullptr);
    removeFromGroup(currentWeapon);
    currentGrid.putWeapon(currentWeapon);
    emit dequipWeaponSignal(currentWeapon);
    currentWeapon->OffsetWeaponGround();
    currentWeapon = nullptr;
}

void Character::DealDamage(int damage)
{
    characterHealth -= damage;
    healthBar->DecrementBar(damage);
    Harmed();
}

void Character::Harmed()
{
    if(characterHealth <= 0)
    {
        dequipWeapon();
        stop();
        emit deadSignal(this);
    }
}

void Character::setRotation(qreal angle) {
    QGraphicsItemGroup::setRotation(angle);
    healthBar->setRotation(-angle -180);

}


bool Character::isPerfectCenterize() const {
    return int(pos().x()) % 32 == 16 &&  int(pos().y()) % 32 == 16;
}


charType Character::getCharacterType()
{
    return typeOfCharacter;
}

void Character::setGridPos(QPoint p) {
    setPos(32 * p.x() + 16, 32 * p.y() + 16);
}

void Character::stop() {
    if (animationX) animationX->stop();
    if (animationY) animationY->stop();
}

void Character::setMoveSpd(int spd) {
    this->spd = spd;
}

int Character::getSpd() const {
    return spd;
}
