#include "gamemapcanvas.h"
#include <QDebug>
#include <QtMath>

GameMapCanvas::GameMapCanvas(QWidget* w) : QGraphicsView(w) {
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

void GameMapCanvas::scrollContentsBy(int, int) {}


void GameMapCanvas::mouseMoveEvent(QMouseEvent* k) {
    qDebug() << "GameMapCanvas::mouseMoveEvent";
    qreal rad = qAtan((k->y() - character->pos().y() + 16) / (k->x() - character->pos().x() + 16));
    character->setRotation(qRadiansToDegrees(rad));
    qDebug() << k->x() << ", " << k->y();
    qDebug() << character->pos().x() << ", " << character->pos().y();
    qDebug() << "rad:" << rad << ", angle: " << qRadiansToDegrees(rad);
}
