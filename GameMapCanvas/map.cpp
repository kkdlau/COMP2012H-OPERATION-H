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
    QFile f{mapConfigFilePath};
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray first_line = f.readLine();
    QList<QByteArray> list =  first_line.split(' ');
    bool success;
    width = list[0].toInt(&success, 10);
    if (success) qDebug() << "width: " << width;
    height = list[0].toInt(&success, 10);
    if (success) qDebug() << "height: " << height;

    for (int y = 0; y < height; ++y) {
        QVector<GridInfo> row;
        for (int x = 0; x < width; ++x) {
            row.push_back(GridInfo{0, x, y});
        }
        grid.push_back(row);
    }

    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        list = line.split(' ');
        int pos_x = list[0].toInt(&success, 10);
        int pos_y = list[1].toInt(&success, 10);
        float height = list[2].toFloat(&success);

        (*this)[pos_y][pos_x].setHeight(height);
        QColor clr = Qt::green;
        clr.setAlphaF(height/ 15.0);
        QBrush tmpBrush{clr};
        QPen tmpPen;
        tmpPen.setColor(Qt::blue);
        tmpPen.setWidth(2);

        addRect(pos_x*32, pos_y*32, 32, 32, tmpPen, tmpBrush);
    }
}

template <typename T>
T Map::getWidth() const {
    if (typeid (T) == typeid (GRID)) return this->width;
    else if (typeid (T) == typeid (PIXEL)) return this->width * Map::GRID_SIZE_W;
    else return NULL;
}

template <typename T>
T Map::getHeight() const {
    if (typeid (T) == typeid (GRID)) return this->height;
    else if (typeid (T) == typeid (PIXEL)) return this->height * Map::GRID_SIZE_H;
    else return NULL;
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
