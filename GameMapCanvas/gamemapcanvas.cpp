#include "gamemapcanvas.h"

#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	map = new Map{this, ":test_map.png"};
	setScene(map);
	setSceneRect(QRectF(0, 0, 320, 320));
	scene = map;
}

void GameMapCanvas::scrollContentsBy(int, int) {}

void GameMapCanvas::mouseMoveEvent(QMouseEvent* e) {
	QGraphicsView::mouseMoveEvent(e);
	qreal x = map->get_cursor_on_map().x() - character->pos().x() + 16;
	qreal y = map->get_cursor_on_map().y() - character->pos().y() + 16;
	qreal rad = qAtan(y / x);
	if (x < 0 && y < 0) rad = M_PI + rad;
	if (x < 0 && y > 0) rad = M_PI + rad;
	qDebug() << "charcater position: " << character->pos().x() << ", "
			 << character->pos().y();
	qDebug() << "rad: " << rad << ", angle: " << qRadiansToDegrees(rad);
	character->setRotation(qRadiansToDegrees(rad));
}
