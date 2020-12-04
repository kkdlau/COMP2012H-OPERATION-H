#include "gamemapcanvas.h"
#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
	setMouseTracking(true);
	setAttribute(Qt::WA_Hover);
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new Overlay{":map_2.png", ":map_2.txt"};
    setScene(scene);
    setSceneRect(QRectF(0, 0, Map::GRID_SIZE_W * 10, Map::GRID_SIZE_H * 10));
}

void GameMapCanvas::mouseMoveEvent(QMouseEvent* e) {
    QGraphicsView::mouseMoveEvent(e);

    qreal x = scene->mapLayer()->getCursorPos().x() - character->pos().x();
    qreal y = scene->mapLayer()->getCursorPos().y() - character->pos().y();
	qreal rad = qAtan(y / x);
    if (x < 0) rad += M_PI;

    character->setRotation(qRadiansToDegrees(rad));
}

GameMapCanvas::~GameMapCanvas() {
    delete scene;
}
