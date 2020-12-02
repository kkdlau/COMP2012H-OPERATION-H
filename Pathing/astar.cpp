#include "astar.h"
#include <QtMath>
#include <QDebug>

int AStar::evaluateCost(QPoint p1, QPoint p2, QPoint end) {
    QPoint diff = p1 - p2;

    /**
     * @brief cost the initial cost is 14 if the movement is diagonal, otherwise 10.
     */
    int cost = (diff.x() == 1 && diff.y() == 1)? 14 : 10;

    // Heuristic Estimate
    return (cost += (qAbs(diff.x()) + qAbs(diff.y())) * 10);
}

void AStar::initialState(QVector<QVector<MapNode>> & state, const Map& map) {
    for (int y = 0, sizeY = map.getHeight(Map::UNIT::GRID); y < sizeY; ++y) {
        state.push_back({});
        for (int x = 0, sizeX = map.getWidth(Map::UNIT::GRID); x < sizeX; ++x) {
            state.last().push_back(MapNode{x, y});
        }
    }
}

int AStar::minCostNode(QList<MapNode>& list) {
    qDebug() << "search min cost";

    int minCost = 9999999;
    int index = 0;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].getCost() < minCost) {
            minCost = list[i].getCost();
            index = i;
        }
    }

    qDebug() << "index: " << index;

    return index;
}

template<typename F>
void AStar::forEachNeighbor(const Map& map, MapNode node, F process) {
    QPoint p{node.getX(), node.getY()};

    if (!map.isOutOfMap(QPoint{p.x() + 1, p.y()}))
        process(p.x() + 1, p.y());

    if (!map.isOutOfMap(QPoint{p.x() - 1, p.y()}))
        process(p.x() - 1, p.y());

    if (!map.isOutOfMap(QPoint{p.x(), p.y() + 1}))
        process(p.x(), p.y() + 1);

    if (!map.isOutOfMap(QPoint{p.x(), p.y() - 1}))
        process(p.x(), p.y() - 1);

}

QList<QPoint> AStar::search(const Map& map, QPoint start, QPoint end) {
    bool success = false;
    QList<MapNode> openList;

    QVector<QVector<MapNode>> mapState;

    initialState(mapState, map);

    openList.push_back(MapNode{start.x(), start.y(), 0});

    do {
        int index = minCostNode(openList);
        MapNode n = openList[index];
        openList.removeAt(index);

        if (n.getX() == end.x() && n.getY() == end.y()) return {};
        mapState[n.getY()][n.getX()].setVisitState(true);

        forEachNeighbor(map, n, [&](int x,int y) {
            if (!mapState[y][x].isVisited()) {
                openList.push_back(MapNode{x, y, evaluateCost(n.toQPoint(), QPoint{x, y}, end)});
            }
        });

    } while (openList.length());
}
