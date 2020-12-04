#include "gamemapcanvas.h"

#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover);
	setAlignment(Qt::AlignTop | Qt::AlignLeft);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GameMapCanvas::createMap(const QString& mapImgPath,
							  const QString& mapConFigPath) {
	layers = new Overlay{mapImgPath, mapConFigPath};
	setScene(layers);
	setSceneRect(QRectF(0, 0, Map::GRID_SIZE_W * 10, Map::GRID_SIZE_H * 10));
}
void GameMapCanvas::mouseMoveEvent(QMouseEvent* e) {
	QGraphicsView::mouseMoveEvent(e);

	qreal x = layers->mapLayer()->getCursorPos().x() - mainCharacter->pos().x();
	qreal y = layers->mapLayer()->getCursorPos().y() - mainCharacter->pos().y();
	qreal rad = qAtan(y / x);
	if (x < 0) rad += M_PI;

	mainCharacter->setRotation(qRadiansToDegrees(rad));
}

void GameMapCanvas::mousePressEvent(QMouseEvent* e) {
	if (mainCharacter) mainCharacter->attack();
}
void GameMapCanvas::setMainCharacter(Character* c) { mainCharacter = c; }

Overlay* GameMapCanvas::gameLayers() { return layers; }

GameMapCanvas::~GameMapCanvas() { delete layers; }
