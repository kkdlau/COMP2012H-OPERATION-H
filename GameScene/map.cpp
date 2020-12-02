#include "map.h"
#include <typeinfo>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QtMath>

const int Map::GRID_SIZE_W = 32;
const int Map::GRID_SIZE_H = 32;

Map::Map(QString imgPath, QString configFilePath): grid{} {
    addToGroup(new QGraphicsPixmapItem{QPixmap(imgPath)});

    parseMapConfigFile(configFilePath);

//    addObstacle(1, 0);
//    addObstacle(1, 1);
//    addObstacle(1, 2);
//    addObstacle(1, 3);

    QList<QPoint> path;
    path.push_back(QPoint{0, 0});
    path.push_back(QPoint{0, 1});
    path.push_back(QPoint{0, 2});

    drawPath(path);
}

void Map::addObstacle(int posX, int posY) {
    (*this)[posY][posX].setHeight(5);
    QColor clr = Qt::blue;
    clr.setAlphaF(0.3);
    QBrush tmpBrush{clr};
    QPen tmpPen;
    QGraphicsRectItem* test_obstacle = new QGraphicsRectItem(0, 0, 32, 32);
    test_obstacle->setPen(tmpPen);
    test_obstacle->setBrush(tmpBrush);
    addToGroup(test_obstacle);
    test_obstacle->setPos(posX * 32.0f, posY *32.0f);
}

void Map::gridInfoinitialize() {
    gridInfoinitialize(width, height);
}

void Map::gridInfoinitialize(int w, int h, int baseHeight) {
    for (int y = 0; y < h; ++y) {
        QVector<GridInfo> row;
        for (int x = 0; x < w; ++x) {
            row.push_back(GridInfo{baseHeight, x, y, this});
        }
        grid.push_back(row);
    }
}

/***
 * Description of Map Configuration file:
 *
 * First line - [width: int] [height: int]: the size of map, in pixel unit
 * Second line and after - [cor_x: int] [cor_y: int] [grid_height: int]: the height of a grid, for configuring grid_height, please refer to character height system.
 *
 */
void Map::parseMapConfigFile(QString mapConfigFilePath) {
    QFile f{mapConfigFilePath};
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray first_line = f.readLine();
    QList<QByteArray> list =  first_line.split(' ');

    bool success;
    width = list[0].toInt(&success, 10);
    height = list[0].toInt(&success, 10);

    this->gridInfoinitialize();

    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        list = line.split(' ');

        /*extract information from line*/
        int pos_x = list[0].toInt(&success, 10);
        int pos_y = list[1].toInt(&success, 10);
        int height = list[2].toFloat(&success);

        (*this)[pos_y][pos_x].setHeight(height);
    }
}


qreal Map::getWidth(Map::UNIT unitRepresent) const {
    switch (unitRepresent) {
    case Map::UNIT::GRID: return width;
    case Map::UNIT::PIXEL: return width * Map::GRID_SIZE_W;
    }
}

qreal Map::getHeight(Map::UNIT unitRepresent) const {
    switch (unitRepresent) {
    case Map::UNIT::GRID: return height;
    case Map::UNIT::PIXEL: return height * Map::GRID_SIZE_H;
    }
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    qDebug() << "update";
    cursorPos = mapFromScene(e->scenePos());
}

QVector<GridInfo>& Map::operator[](const unsigned columnIndex) {
    return grid[columnIndex];
}

const QVector<GridInfo>& Map::operator[](const unsigned columnIndex) const {
    return grid[columnIndex];
}

GridInfo& Map::operator[](const QPoint& p) {
    return grid[p.y()][p.x()];
}

const GridInfo& Map::operator[](const QPoint& p) const {
    return grid[p.y()][p.x()];
}

void Map::updateCursorPos(QPointF p) {
    cursorPos = p;
}

const QPointF& Map::getCursorPos() const { return cursorPos; }

bool Map::isOutOfMap(const QPoint& p) const {
    return p.x() < 0 || p.y() < 0 || p.x() >= this->width || p.y() >= this->height;
}

bool Map::isOutOfMap(const QPointF& p, qreal* x, qreal* y) const {
    if (isOutOfMap(p.toPoint())) {
        if (p.x() < 0) *x = p.x();
        else *x = p.x() - getWidth(Map::UNIT::GRID);

        if (p.y() < 0) *y = p.y();
        else *y = p.y() - getHeight(Map::UNIT::GRID);
        return true;
    } else return false;
}

bool Map::isAccessible(const QPoint &from, const QPoint &to, const int stepValue) const {
    if (isOutOfMap(to)) return false;
    if (abs(from.x() - to.x()) == 1 && abs(from.y() - to.y()) == 1) {
        /*diagonal neighbor checking*/
        return (*this)[from] - (*this)[to] <= stepValue &&
                (*this)[from] - (*this)[QPoint{from.x(), to.y()}] <= stepValue &&
                (*this)[from] - (*this)[QPoint{to.x(), from.y()}] <= stepValue;
    } else if ((abs(from.x() - to.x()) == 1 && abs(from.y() - to.y()) == 0) ||
                (abs(from.x() - to.x()) == 0 && abs(from.y() - to.y()) == 1)) {
        /*directional neighbor checking*/
        return (*this)[from] - (*this)[to] <= stepValue;
    } return false;
}

void Map::drawPath(QList<QPoint> path) {
    QList<QPoint>::iterator ptr;
    QList<QPoint>::iterator end = path.end() - 1;
    for (ptr = path.begin(); ptr < end; ++ptr) {
        QPoint p = *ptr;
        QPoint nextP = *(ptr + 1);
        QGraphicsRectItem* rect = new QGraphicsRectItem{p.x() * 32.0f + 10, p.y() * 32.0f + 10, 12, 12};
        rect->setBrush(Qt::black);
        addToGroup(new QGraphicsLineItem{p.x() * 32.0f + 16, p.y() * 32.0f + 16, nextP.x() * 32.0f + 16, nextP.y() * 32.0f + 16});
        addToGroup(rect);
    }

    QGraphicsRectItem* rect = new QGraphicsRectItem{path.last().x() * 32.0f + 10, path.last().y() * 32.0f + 10, 12, 12};
    addToGroup(rect);
}

Map::~Map() {}
