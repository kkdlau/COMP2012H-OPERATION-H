#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPointF>
#include <QString>
#include <QWidget>
#include <QVector>
#include "gridinfo.h"

class Map : public QGraphicsScene {
   private:
	QString mapName;
	QPixmap* mapImg;
	QPointF cursorPos;
    QVector<QVector<GridInfo>> grid;
    unsigned int width;
    unsigned int height;


   public:
    static const unsigned short GRID_SIZE_W;
    static const unsigned short GRID_SIZE_H;
    Map(QObject* parent, QString resourceName, QString mapConfigFilePath);

	void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;

	const QPointF& get_cursor_on_map() const;
    QVector<GridInfo>& operator[](const unsigned columnIndex);
    const QVector<GridInfo>& operator[](const unsigned columnIndex) const;
	~Map();
};

#endif	// MAP_H
