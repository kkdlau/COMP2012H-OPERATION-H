#ifndef GAMPMAPCANVAS_H
#define GAMPMAPCANVAS_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>
#include "./map.h"

class GameMapCanvas : public QGraphicsView {
   public:
    GameMapCanvas(QWidget* widget);
    Map* map;

    QGraphicsPixmapItem *character;
    QGraphicsScene *scene;

	void scrollContentsBy(int, int) override;

    void mouseMoveEvent(QMouseEvent* k);
};

#endif	// GAMPMAPCANVAS_H
