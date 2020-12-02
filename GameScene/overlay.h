#ifndef OVERLAY_H
#define OVERLAY_H
#include <QGraphicsScene>
#include "QGraphicsItemGroup"
#include "UI/itemframe.h"
#include "GameScene/map.h"

class Overlay: public QGraphicsScene
{
public:
    Overlay(QString imgPath, QString configFilePath);
    Map* mapLayer();
    ItemFrame* getItemFrame();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    ItemFrame *itemFrame = nullptr;
    Map *map = nullptr;
};

#endif // OVERLAY_H
