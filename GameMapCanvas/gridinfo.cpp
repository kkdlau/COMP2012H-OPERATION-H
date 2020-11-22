#include "gridinfo.h"

GridInfo::GridInfo(float height, unsigned int x, unsigned int y/*, QVector<Weapon>&& weapons = {}*/):
    height{height}, x{x}, y{y}/*, weapons{weapons}*/
{

}

float GridInfo::getHeight() const {
    return height;
}

void GridInfo::setHeight(const float height) {
    this->height = height;
}

QString GridInfo::toString() const {
    return QString("(%1, %2)").arg("%1", QString::number(x)).arg("%2", QString::number(y));
}

//const QVector<Weapon>& GridInfo::getWeapons() const {
//    return weapons;
//}

//QVector<Weapon>& GridInfo::getWeapons() {
//    return weapons;
//}
