#include "map.h"
#include <QDebug>

Map::Map(QObject *parent, QString resourceName): QGraphicsScene{parent} {
    mapImg = new QPixmap(resourceName);
    addPixmap(*mapImg);
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    QGraphicsScene::mouseMoveEvent(e);
    cursorPos = e->scenePos();
    qDebug() << "Map::mouseMoveEvent: " << e;
}

const QPointF& Map::get_cursor_on_map() const {
    return cursorPos;
}

Map::~Map() {
    delete mapImg;
}
