#include "gamemapcanvas.h"

#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    map = new Map{this, ":test_map.png", ":test_map.txt"};
	setScene(map);
    setSceneRect(QRectF(0, 0, Map::GRID_SIZE_W * 10, Map::GRID_SIZE_H * 10));
	scene = map;
}

void GameMapCanvas::scrollContentsBy(int, int) {}

void GameMapCanvas::mouseMoveEvent(QMouseEvent* e) {
	QGraphicsView::mouseMoveEvent(e);
    qreal x = map->get_cursor_on_map().x() - character->pos().x() + Map::GRID_SIZE_W / 2;
    qreal y = map->get_cursor_on_map().y() - character->pos().y() + Map::GRID_SIZE_H / 2;
	qreal rad = qAtan(y / x);
	if (x < 0 && y < 0) rad = M_PI + rad;
	if (x < 0 && y > 0) rad = M_PI + rad;
	character->setRotation(qRadiansToDegrees(rad));
}
