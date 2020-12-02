#include "gridinfo.h"
#include <QtMath>
#include "map.h"
#include <QDebug>

GridInfo::GridInfo(int height, int x, int y):
    height{height}, x{x}, y{y}
{

}

GridInfo::GridInfo(const GridInfo& grid): height{grid.height}, x{grid.x}, y{grid.y} {
}

int GridInfo::getHeight() const {
    return height;
}

void GridInfo::setHeight(const int height) {
    this->height = height;
    qDebug() << "setHeight";
}

QString GridInfo::toString() const {
    return QString("(%1, %2): %3").arg(QString::number(x)).arg(QString::number(y)).arg(QString::number(height));
}

int GridInfo::heightDiff(const GridInfo &grid) const {
    return abs(height - grid.height);
}

void GridInfo::AddWeaponToGrid(Weapon *data)
{
    weapon = data;
}

bool GridInfo::IsWeaponInGrid()
{
    return weapon;
}

Weapon *GridInfo::GetWeaponData()
{
    Weapon* temp = weapon;
    weapon = nullptr;
    return temp;
}

QPointF GridInfo::GetPosition()
{
    QPointF data(x * 32, y * 32);
    return data;
}
