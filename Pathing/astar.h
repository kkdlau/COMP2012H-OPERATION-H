#ifndef PATHING_H
#define PATHING_H
#include "GameMapCanvas/map.h"
#include <QList>
#include <QVector>
class AStar
{
public:
    AStar() = delete;

    class MapNode {
    private:
        int x;
        int y;
        bool visited{false};
        int cost{-1};
        MapNode* parent{nullptr};
    public:
        MapNode(int x, int y): x{x}, y{y} {}
        MapNode(int x, int y, int cost, MapNode* parent = nullptr): x{x}, y{y}, cost{cost}, parent{parent} {}

        void setVisitState(bool state) {visited = state;}

        void setCost(int cost) {this->cost = cost;}

        bool isVisited() const {return visited;}

        int getCost() const {return cost;}

        int getX() const {return x;}

        int getY() const {return y;}

        QPoint toQPoint() const {return QPoint{x, y};}

        ~MapNode() {}
    };

    static int minCostNode(QList<MapNode>& list);

    static int evaluateCost(QPoint p1, QPoint p2, QPoint end);

    static void initialState(QVector<QVector<MapNode>>& state, const Map& map);

    template<typename F>
    static void forEachNeighbor(const Map& map,MapNode node, F process);

    static QList<QPoint> search(const Map& map, QPoint start, QPoint end);
};

#endif // PATHING_H
