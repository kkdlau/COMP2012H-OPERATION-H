#include "overlay.h"

Overlay::Overlay(QString imgPath, QString configFilePath) {

    map = new Map(imgPath, configFilePath);
    itemFrame = new ItemFrame();
    addItem(map);
    addItem(itemFrame);
}

void Overlay::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mousePressEvent(mouseEvent);
    mapLayer()->updateCursorPos(mapLayer()->mapFromScene(mouseEvent->scenePos()));
}

Map* Overlay::mapLayer()
{
    return map;
}
