#ifndef GAMPMAPCANVAS_H
#define GAMPMAPCANVAS_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include "GameCharacter/character.h"
#include "GameScene/overlay.h"

class Camera;

class GameMapCanvas : public QGraphicsView {
    Overlay* layers{nullptr};
    Character* mainCharacter{nullptr};

public:
    GameMapCanvas(QWidget* widget);

    void mouseMoveEvent(QMouseEvent* k) override;
    void mousePressEvent(QMouseEvent* k) override;

    /**
     * @brief createMap Create a game map and register the map into the canvas.
     * @param mapImgPath Map Image Resource Path
     * @param mapConFigPath Map Configuration Resource path
     */
    void createMap(const QString& mapImgPath, const QString& mapConFigPath);

    /**
     * @brief gameLayers Get layers of the canvas
     * @return the layers of canvas
     */
    Overlay* gameLayers();

    Character* getMainCharacter();

    void setMainCharacter(Character* c);


    ~GameMapCanvas();
};

#include "camera.h"

#endif	// GAMPMAPCANVAS_H
