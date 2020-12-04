#include "overlay.h"

Overlay::Overlay(QString imgPath, QString configFilePath) {

    map = new Map(imgPath, configFilePath);
    itemFrame = new ItemFrame();
    addItem(map);
    addItem(itemFrame);
}

Overlay::~Overlay()
{
    delete map;
    map = nullptr;
    delete itemFrame;
    itemFrame = nullptr;
}

void Overlay::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mousePressEvent(mouseEvent);
    mapLayer()->updateCursorPos(mapLayer()->mapFromScene(mouseEvent->scenePos()));
}

ItemFrame* Overlay::getItemFrame()
{
    return itemFrame;
}

Map* Overlay::mapLayer()
{
    return map;
}
