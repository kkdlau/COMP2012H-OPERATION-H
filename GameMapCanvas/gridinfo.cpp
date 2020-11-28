#include "gridinfo.h"
#include <QtMath>
#include "map.h"
#include <QDebug>

GridInfo::GridInfo(int height, int x, int y):
    height{height}, x{x}, y{y}
{
    collidingRect = new QGraphicsRectItem{.0f, .0f, 32.0f, 32.0f};
    updateCollidingRect();
}

GridInfo::GridInfo(const GridInfo& grid): height{grid.height}, x{grid.x}, y{grid.y} {
    collidingRect = new QGraphicsRectItem{grid.collidingRect->rect()};
    updateCollidingRect();
}

QGraphicsRectItem* GridInfo::getCollidingRect() const {
    return collidingRect;
}

void GridInfo::updateCollidingRect() {
    collidingRect->setVisible(false);
    collidingRect->setPos(x * Map::GRID_SIZE_W, y * Map::GRID_SIZE_H);
}

void GridInfo::registerCollidingRect(QGraphicsRectItem* rect) {
    collidingRect = rect;
    updateCollidingRect();
}

int GridInfo::getHeight() const {
    return height;
}

void GridInfo::setHeight(const int height) {
    this->height = height;
    qDebug() << "setHeight";
    updateCollidingRect();
}

QString GridInfo::toString() const {
    return QString("(%1, %2)").arg("%1", QString::number(x)).arg("%2", QString::number(y));
}

int GridInfo::heightDiff(const GridInfo &grid) const {
    return abs(height - grid.height);
}
