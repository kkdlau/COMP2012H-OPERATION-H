#include "overlay.h"

Overlay::Overlay(QString imgPath, QString configFilePath) {

    map = new Map(imgPath, configFilePath);
    itemFrame = new ItemFrame();
    addItem(map);
    addItem(itemFrame);
}

Map* Overlay::mapLayer()
{
    return map;
}
