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
//    windowWidth = size.width();
//    windowHeight = size.height();
    windowWidth = 320;
    windowHeight = 320;
    qDebug() << "window width: " << windowWidth;
    qDebug() << "window height: " << windowHeight;
}

void Camera::registerCanvas(GameMapCanvas *canvas) {
    if (canvas == nullptr) return;
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
    unsubscribe();
    cameraMoveConnection = connect(owner, funcs, this, &Camera::updateFocus);
}

void Camera::updateFocus(QPointF p) {
    updateHorizontalFocus(p.x());
    updateVerticalFocus(p.y());
}

void Camera::updateVerticalFocus(qreal v) {
    const int heightHalf = windowHeight / 2;
    const int mapHeight = canvas->map->getHeight(Map::UNIT::PIXEL);

    if (v <= heightHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setY(0);
        canvas->setSceneRect(rect);
    } else if (v >= mapHeight - heightHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setY(mapHeight - windowHeight);
        canvas->setSceneRect(rect);
    } else {
        QRectF rect = canvas->sceneRect();
        rect.setY(v - heightHalf);
        canvas->setSceneRect(rect);
    }
}

void Camera::updateHorizontalFocus(qreal h) {
    const int widthtHalf = windowWidth / 2;
    const int mapHeight = canvas->map->getWidth(Map::UNIT::PIXEL);

    if (h <= widthtHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setX(0);
        canvas->setSceneRect(rect);
    } else if (h >= mapHeight - widthtHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setX(mapHeight - windowHeight);
        canvas->setSceneRect(rect);
    } else {
        QRectF rect = canvas->sceneRect();
        rect.setX(h - widthtHalf);

        canvas->setSceneRect(rect);
    }
}

Camera::~Camera() {
    unsubscribeCanvasSizeEvent();
    unsubscribe();

}
