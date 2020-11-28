#ifndef GAMPMAPCANVAS_H
#define GAMPMAPCANVAS_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include "../character.h"

#include "./map.h"

class GameMapCanvas : public QGraphicsView {
   public:
	GameMapCanvas(QWidget* widget);
	Map* map;

    Character* character;
	QGraphicsScene* scene;

	void scrollContentsBy(int, int) override;

    void mouseMoveEvent(QMouseEvent* k) override;
};

#endif	// GAMPMAPCANVAS_H
