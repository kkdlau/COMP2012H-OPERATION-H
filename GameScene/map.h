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
#include <QGraphicsItemGroup>
using GRID = int;
using PIXEL = qreal;

class Map : public QGraphicsItemGroup {
   private:
	QPointF cursorPos;
    QVector<QVector<GridInfo>> grid;
    int width;
    int height;

    /**
     * @brief parseMapConfigFile Parse Map Configuration File
     * @param mapConfigFilePath path to the file
     */
    void parseMapConfigFile(QString mapConfigFilePath);

    /**
     * @brief gridInfoinitialize helper function to initialize the whole map
     */
    void gridInfoinitialize();

    /**
     * @brief gridInfoinitialize initialize the grid info of the map, the range is specified
     * @param w width of the map
     * @param h height of the map
     * @param baseHeight the base height, i.e. height of ground
     */
    void gridInfoinitialize(int w, int h, int baseHeight = 0);

   public:
    enum class UNIT {PIXEL, GRID};
    static const int GRID_SIZE_W;
    static const int GRID_SIZE_H;

    Map(const QString& imgPath, const QString& configFilePath);

	void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;

    /**
     * @brief updateCursorPos Update cursor position
     * @param p scene position
     */
    void updateCursorPos(QPointF p);

    /**
     * @brief getCursorPos Get the cursor position
     * @return Position of cursor
     */
    const QPointF& getCursorPos() const;

    /**
     * @brief operator [] access the grid info of the whole row via column index.
     * @param columnIndex index of y, should be in GRID unit
     * @return row of grid info
     */
    QVector<GridInfo>& operator[](const unsigned columnIndex);

    /**
     * @brief operator [] access the grid info of the whole row via column index.
     * @param columnIndex index of y, should be in GRID unit
     * @return row of grid info
     */
    const QVector<GridInfo>& operator[](const unsigned columnIndex) const;

    /**
     * @brief operator [] access the grid info via point.
     * @param p Point to access, should be in GRID unit.
     * @return grid info to get
     */
    GridInfo& operator[](const QPoint& p);

    /**
     * @brief operator [] access the grid info via point.
     * @param p Point to access, should be in GRID unit.
     * @return grid info to get
     */
    const GridInfo& operator[](const QPoint& p) const;

    /**
     * @brief isOutOfMap Check if the grid position is within the map boundary. Returns false if it's out of map boundary.
     * @param p Point to check
     * @return Out of map or not
     */
    bool isOutOfMap(const QPoint& p) const;

    /**
     * @brief isOutOfMap Check if the given pixel coordinate is within the map boundary. If not, the offset will be passed through the X and Y parameter.
     * @param p Point to check
     * @param x If out of map, the overshoot / undershoot of x-axis will be assigned to this pointer
     * @param y If out of map, the overshoot / undershoot of y-axis will be assigned to this pointer
     * @return Out of map or not
     */
    bool isOutOfMap(const QPointF& p, qreal* x, qreal* y) const;

    /**
     * @brief isAccessible Check is the grid accessible. Please note that this is not pathing searching. It is only available for neighbor grid.
     * @param from Starting point
     * @param to End point. Should be a neighbor of starting point
     * @param stepValue Step value, how "high" can the target travel
     * @return accessible or not
     */
    bool isAccessible(const QPoint& from, const QPoint& to, const int stepValue) const;

    /**
     * @brief addObstacle Helper function for adding obstacle onto the map
     * @param posX grid x coordinate
     * @param posY grid y coordinate
     */
    void addObstacle(int posX, int posY);


    /**
     * @brief getWidth Get the width of map
     * @param unitRepresent Representation unit
     * @return width in the corresponding unit
     */
    qreal getWidth(UNIT unitRepresent) const;

    /**
     * @brief getHeight Get the height of map
     * @param unitRepresent Representation unit
     * @return height in the corresponding unit
     */
    qreal getHeight(UNIT unitRepresent) const;

    /**
     * @brief drawPath helper function for drawing path
     * @param path Path generated from pathing algorithm
     */
    void drawPath(QList<QPoint> path);

    QList<QGraphicsItem*> tempVar;
	~Map();
};

#endif	// MAP_H
