#ifndef GAMPMAPCANVAS_H
#define GAMPMAPCANVAS_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include "../character.h"
#include "GameScene/overlay.h"

class Camera;

class GameMapCanvas : public QGraphicsView {
   public:
	GameMapCanvas(QWidget* widget);
    Camera* cameraController;

    Character* character;
    Overlay* scene;

    void scrollContentsBy(int dx, int dy) override;

    void mouseMoveEvent(QMouseEvent* k) override;

    ~GameMapCanvas();
};

#include "camera.h"

#endif	// GAMPMAPCANVAS_H
