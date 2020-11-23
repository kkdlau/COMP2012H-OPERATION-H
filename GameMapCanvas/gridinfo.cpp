#include "gridinfo.h"
#include <QtMath>

GridInfo::GridInfo(int height, int x, int y/*, QVector<Weapon>&& weapons = {}*/):
    height{height}, x{x}, y{y}/*, weapons{weapons}*/
{

}

int GridInfo::getHeight() const {
    return height;
}

void GridInfo::setHeight(const int height) {
    this->height = height;
}

QString GridInfo::toString() const {
    return QString("(%1, %2)").arg("%1", QString::number(x)).arg("%2", QString::number(y));
}

int GridInfo::heightDiff(const GridInfo &grid) const {
    return abs(height - grid.height);
}

//const QVector<Weapon>& GridInfo::getWeapons() const {
//    return weapons;
//}

//QVector<Weapon>& GridInfo::getWeapons() {
//    return weapons;
//}
