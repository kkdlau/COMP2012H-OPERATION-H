#include "gamemapcanvas.h"
#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map = new Map{this, ":map_2.png", ":map_2.txt"};
	setScene(map);
    setSceneRect(QRectF(0, 0, Map::GRID_SIZE_W * 10, Map::GRID_SIZE_H * 10));
	scene = map;

    cameraController = new Camera;

    cameraController->registerCanvas(this);
}

void GameMapCanvas::scrollContentsBy(int dx, int dy) {
    QGraphicsView::scrollContentsBy(dx, dy);
}

void GameMapCanvas::mouseMoveEvent(QMouseEvent* e) {
    QGraphicsView::mouseMoveEvent(e);

//    map->displayLayer()->mapFromScene(e->);

    qreal x = map->get_cursor_on_map().x() - character->pos().x();
    qreal y = map->get_cursor_on_map().y() - character->pos().y();
	qreal rad = qAtan(y / x);
    if (x < 0) rad += M_PI;

    character->setRotation(qRadiansToDegrees(rad));
}

GameMapCanvas::~GameMapCanvas() {
    delete cameraController;
}
