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
    qDebug() << p;
    updateHorizontalFocus(p.x());
    updateVerticalFocus(p.y());

    qDebug() << canvas->sceneRect();
}

void Camera::updateVerticalFocus(qreal v) {
    const int heightHalf = windowHeight / 2;
    const int mapHeight = canvas->map->getHeight(Map::UNIT::PIXEL);


    if (v <= heightHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setY(0);
        rect.setHeight(windowHeight);
        canvas->setSceneRect(rect);
    } else if (v >= mapHeight - heightHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setY(mapHeight - windowHeight);
        rect.setHeight(windowHeight);
        canvas->setSceneRect(rect);
    } else {
        QRectF rect = canvas->sceneRect();
        rect.setY(v - heightHalf);
        rect.setHeight(windowHeight);
        canvas->setSceneRect(rect);
    }
}

void Camera::updateHorizontalFocus(qreal h) {
    const int widthHalf = windowWidth / 2;
    const int mapWidth = canvas->map->getWidth(Map::UNIT::PIXEL);

    if (h <= widthHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setX(0);
        rect.setWidth(windowWidth);
        canvas->setSceneRect(rect);
    } else if (h >= mapWidth - widthHalf) {
        QRectF rect = canvas->sceneRect();
        rect.setX(mapWidth - windowHeight);
        rect.setWidth(windowWidth);
        canvas->setSceneRect(rect);
    } else {
        QRectF rect = canvas->sceneRect();
        rect.setX(h - widthHalf);
        rect.setWidth(windowWidth);
        canvas->setSceneRect(rect);
    }
}

Camera::~Camera() {
    unsubscribeCanvasSizeEvent();
    unsubscribe();

}
