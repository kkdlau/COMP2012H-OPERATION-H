#include "gamemapcanvas.h"
#include "camera.h"
#include <QDebug>

Camera::Camera(GameMapCanvas* canvas, Character* c) {
    registerCanvas(canvas);
    subscribe(c, &Character::isMoving);
}

void Camera::unsubscribeCanvasSizeEvent() {
    if (canvasSizeChangeConnection) {
        disconnect(canvasSizeChangeConnection);
    }
}

void Camera::updateCanvasSize(QSizeF size) {
    windowWidth = size.width();
    windowHeight = size.height();
}

void Camera::registerCanvas(GameMapCanvas *canvas) {
    if (!canvas) return;
    this->canvas = canvas;

//    canvasSizeChangeConnection = connect(canvas, &QGraphicsView::resize, this, &Camera::updateCanvasSize);
    QSizeF size = canvas->sceneRect().size();
    updateCanvasSize(size);
}

void Camera::unsubscribe() {
    if (cameraMoveConnection) {
        disconnect(cameraMoveConnection);
    }
}

template<typename funcOwner, typename functionPointer>
void Camera::subscribe(funcOwner owner, functionPointer funcs) {
    if (!owner) return;
    unsubscribe();
    cameraMoveConnection = connect(owner, funcs, this, &Camera::updateFocus);
}

void Camera::updateFocus(QPointF p) {
    if (!canvas) return;
    updateHorizontalFocus(p.x());
    updateVerticalFocus(p.y());
}

void Camera::updateVerticalFocus(qreal v) {
    const int heightHalf = windowHeight / 2;
    const int mapHeight = canvas->scene->mapLayer()->getHeight(Map::UNIT::PIXEL);


    if (v <= heightHalf) {
        canvas->scene->mapLayer()->setY(0);
    } else if (v >= mapHeight - heightHalf) {
        canvas->scene->mapLayer()->setY(-(mapHeight - windowHeight));
    } else {
        canvas->scene->mapLayer()->setY(-(v - heightHalf));
    }
}

void Camera::updateHorizontalFocus(qreal h) {
    const int widthHalf = windowWidth / 2;
    const int mapWidth = canvas->scene->mapLayer()->getWidth(Map::UNIT::PIXEL);

    if (h <= widthHalf) {
        canvas->scene->mapLayer()->setX(0);
    } else if (h >= mapWidth - widthHalf) {
        canvas->scene->mapLayer()->setX(-(mapWidth - windowHeight));
    } else {
        canvas->scene->mapLayer()->setX(-(h - widthHalf));
    }
}

Camera::~Camera() {
    unsubscribeCanvasSizeEvent();
    unsubscribe();

}
