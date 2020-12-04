#ifndef OVERLAY_H
#define OVERLAY_H
#include <QGraphicsScene>
#include "QGraphicsItemGroup"
#include "UI/itemframe.h"
#include "GameScene/map.h"

class Overlay: public QGraphicsScene
{
public:
    /**
     * @brief Overlay is a QGraphicsScene that acts a UI layer to the map
     * @param imgPath is the map image path
     * @param configFilePath is the collider configuration for the map
     */
    Overlay(QString imgPath, QString configFilePath);
    ~Overlay();
    /**
     * @brief mapLayer returns the Map* gamedata
     * @return Map*
     */
    Map* mapLayer();
    /**
     * @brief getItemFrame returns the ItemFrame
     * @return ItemFrame*
     */
    ItemFrame* getItemFrame();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    /**
     * @brief holds the itemFrame being used in the UI
     */
    ItemFrame *itemFrame = nullptr;
    /**
     * @brief holds the Map data being used for the game
     */
    Map *map = nullptr;
};

#endif // OVERLAY_H
