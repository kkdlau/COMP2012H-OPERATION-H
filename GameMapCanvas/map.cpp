#include "map.h"
#include <typeinfo>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QtMath>

const int Map::GRID_SIZE_W = 32;
const int Map::GRID_SIZE_H = 32;

Map::Map(QObject* parent, QString resourceName, QString mapConfigFilePath) : QGraphicsScene{parent}, grid{} {
	mapImg = new QPixmap(resourceName);
	addPixmap(*mapImg);

    parseMapConfigFile(mapConfigFilePath);
    setSceneRect(0, 0, 320, 320);
}

void Map::addObstacle(int posX, int posY) {
    (*this)[posY][posX].setHeight(5);
    QColor clr = Qt::blue;
    clr.setAlphaF(0.3);
    QBrush tmpBrush{clr};
    QPen tmpPen;
    test_obstacle = addRect(0, 0, 32, 32, tmpPen, tmpBrush);
    test_obstacle->setPos(posX * 32.0f, posY *32.0f);
}

void Map::gridInfoinitialize() {
    gridInfoinitialize(width, height);
}

void Map::gridInfoinitialize(int w, int h, int baseHeight) {
    for (int y = 0; y < h; ++y) {
        QVector<GridInfo> row;
        for (int x = 0; x < w; ++x) {
            row.push_back(GridInfo{baseHeight, x, y});
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
	QGraphicsScene::mouseMoveEvent(e);
	cursorPos = e->scenePos();
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

const QPointF& Map::get_cursor_on_map() const { return cursorPos; }

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

Map::~Map() { delete mapImg; }
