#include "astar.h"
#include <QtMath>
#include <QDebug>

AStar::AStar(const Map& map): map{map} {

}

AStar::AStar(const AStar& pathingInstance): map{pathingInstance.map} {
    start = pathingInstance.start;
    end = pathingInstance.end;
}

QList<QPoint> AStar::search(QPoint start, QPoint end, int stepValue) {
    this->start = start;
    this->end = end;

    QList<MapNode*> openList;

    QVector<QVector<MapNode>> mapState;

    initialState(mapState);
    mapState[start.y()][start.x()].state = MapNode::State::OPEN;

    openList.push_back(&mapState[start.y()][start.x()]);

    do {
        int index = minCostNode(openList);
        MapNode& n = *openList[index];
        openList.removeAt(index);
        n.state = MapNode::State::CLOSE;

        if (n.x == end.x() && n.y == end.y()) {
            QList<QPoint> toReturn;

            toReturn.push_back(n.toQPoint());
            MapNode* _n = &n;
            while (_n->parent) {
                toReturn.push_front(_n->toQPoint());
                _n = _n->parent;
            }

            toReturn.push_front(_n->toQPoint());

            return toReturn;
        };

        forEachNeighbor(n, stepValue,[&](int x,int y) {
            //            qDebug() << "visit" << mapState[y][x].toString();
            MapNode& node = mapState[y][x];
            if (node.state == MapNode::State::NONE) {
                node.gCost = evaluateGCost(n, node);
                node.hCost = evaluateHCost(node);
                node.cost = node.gCost + node.hCost;
                node.state = MapNode::State::OPEN;
                node.parent = &n;
                openList.push_back(&node);
            } else if (node.state == MapNode::State::OPEN) {
                if (evaluateCost(n, node) < node.cost) {
                    //                    qDebug() << "change parent:" << node.toQPoint() << " - from:"  << node.parent->toQPoint() << " to " << n.toQPoint();
                    node.gCost = evaluateGCost(n, node);
                    node.hCost = evaluateHCost(node);
                    node.cost = node.gCost + node.hCost;
                    node.state = MapNode::State::OPEN;
                    node.parent = &n;
                }
            }
        });
    } while (openList.length());

    return {};
}

int AStar::evaluateGCost(const MapNode& from, const MapNode& to) const {
    QPoint diff = from.toQPoint() - to.toQPoint();

    /**
     * @brief cost the initial cost is 14 if the movement is diagonal, otherwise 10.
     */
    int cost = (qAbs(diff.x()) == 1 && qAbs(diff.y()) == 1)? 14 : 10;
    return cost + from.gCost;
}

int AStar::evaluateHCost(const MapNode& current) const {
    QPoint diff = current.toQPoint() - end;
    return qAbs(diff.x()) + qAbs(diff.y()) * 10;
}

int AStar::evaluateCost(MapNode& from, MapNode& to) const {
    return evaluateGCost(from, to) + evaluateHCost(to);
}

void AStar::initialState(QVector<QVector<MapNode>> & mapNodeList) const {
    for (int y = 0, sizeY = map.getHeight(Map::UNIT::GRID); y < sizeY; ++y) {
        mapNodeList.push_back({});
        for (int x = 0, sizeX = map.getWidth(Map::UNIT::GRID); x < sizeX; ++x) {
            mapNodeList.last().push_back(MapNode{x, y});
        }
    }
}

int AStar::minCostNode(QList<MapNode*>& list) const {
//    qDebug() << "search min cost";

    int minCost = 9999999;
    int index = 0;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i]->cost < minCost) {
            minCost = list[i]->cost;
            index = i;
        }
    }

//    qDebug() << "index: " << index;

    return index;
}

template<typename F>
void AStar::forEachNeighbor(const MapNode& node, int stepValue, F process) const {
    QPoint p{node.x, node.y};
    QList<QPoint> neighbors = {
        QPoint{p.x() + 1, p.y() + 1},
        QPoint{p.x() - 1, p.y() + 1},
        QPoint{p.x() - 1, p.y() - 1},
        QPoint{p.x() + 1, p.y() - 1},
        QPoint{p.x() + 1, p.y()},
        QPoint{p.x() - 1, p.y()},
        QPoint{p.x(), p.y() + 1},
        QPoint{p.x(), p.y() - 1}

    };

    QList<QPoint>::iterator ptr;

    for (ptr = neighbors.begin(); ptr < neighbors.end(); ++ptr) {
        QPoint tmp = *ptr;

//        qDebug() << "check neighbor: " << tmp << "- access?:" << map.isAccessible(p, tmp, 1);
        if (!map.isOutOfMap(tmp) && map.isAccessible(p, tmp, stepValue))
            process(tmp.x(), tmp.y());
    }

}
