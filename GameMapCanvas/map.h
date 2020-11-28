#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPointF>
#include <QString>
#include <QWidget>
#include <QVector>
#include "gridinfo.h"

using GRID = int;
using PIXEL = qreal;

class Map : public QGraphicsScene {
   private:
	QString mapName;
	QPixmap* mapImg;
	QPointF cursorPos;
    QVector<QVector<GridInfo>> grid;
    int width;
    int height;

    void parseMapConfigFile(QString mapConfigFilePath);

    /**
     * @brief gridInfoinitialize helper function for initializing the whole map
     */
    void gridInfoinitialize();

    /**
     * @brief gridInfoinitialize initialize the grid info of map, the range is specified
     * @param w width of the map
     * @param h height of the map
     * @param baseHeight the base height, i.e. height of ground
     */
    void gridInfoinitialize(int w, int h, int baseHeight = 0);

   public:
    static const int GRID_SIZE_W;
    static const int GRID_SIZE_H;
    QGraphicsRectItem* test_obstacle;

    Map(QObject* parent, QString resourceName, QString mapConfigFilePath);

	void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;

	const QPointF& get_cursor_on_map() const;
    QVector<GridInfo>& operator[](const unsigned columnIndex);
    const QVector<GridInfo>& operator[](const unsigned columnIndex) const;

    GridInfo& operator[](const QPoint& p);
    const GridInfo& operator[](const QPoint& p) const;

    bool isOutOfMap(const QPoint& p) const;
    bool isOutOfMap(const QPointF& p, qreal* x, qreal* y) const;
    bool isAccessible(const QPoint& from, const QPoint& to, const int stepValue) const;


    template<typename T>
    /**
     * @brief getWidth: get width of map. T should be either GRID or PIXEL.
     * @return width of map
     */
    T getWidth() const;

    template<typename T>
    /**
     * @brief getHeight: get height of map. T should be either GRID or PIXEL.
     * @return height of map
     */
    T getHeight() const;
	~Map();
};

#endif	// MAP_H
