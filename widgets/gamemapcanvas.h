#ifndef GAMPMAPCANVAS_H
#define GAMPMAPCANVAS_H
#include <QGraphicsView>

class GameMapCanvas : public QGraphicsView {
   public:
	GameMapCanvas(QWidget* widget);

	void scrollContentsBy(int, int) override;
};

#endif	// GAMPMAPCANVAS_H
