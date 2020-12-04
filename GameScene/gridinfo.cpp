#include "gridinfo.h"
#include <QtMath>
#include "map.h"
#include <QDebug>

GridInfo::GridInfo(int height, int x, int y, QGraphicsItemGroup* belongLayer):
    height{height}, x{x}, y{y}, renderlayer{belongLayer}
{

}

GridInfo::GridInfo(const GridInfo& grid): height{grid.height}, x{grid.x}, y{grid.y}, renderlayer{grid.renderlayer} {
}

int GridInfo::getHeight() const {
    return height;
}

void GridInfo::setHeight(const int height) {
    this->height = height;
}

QString GridInfo::toString() const {
    return QString("(%1, %2): %3, hasWeapon?:%4").arg(QString::number(x)).arg(QString::number(y)).arg(QString::number(height)).arg(QString::number(weapon != nullptr));
}

int GridInfo::heightDiff(const GridInfo &grid) const {
    return abs(height - grid.height);
}

void GridInfo::putWeapon(Weapon *data) {
    weapon = data;
    weapon->setPos(x * 32 + 16, y * 32 + 16);
    renderlayer->addToGroup(weapon);
}

bool GridInfo::isWeaponOnGround() const {
    return weapon != nullptr;
}

void GridInfo::removeWeapon() {
    renderlayer->removeFromGroup(weapon);
    weapon = nullptr;
}

Weapon *GridInfo::popWeapon()
{
    Weapon* temp = weapon;
    removeWeapon();
    return temp;
}

QPoint GridInfo::getPos() const {
    return QPoint{x, y};
}
