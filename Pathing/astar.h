#ifndef PATHING_H
#define PATHING_H
#include "GameScene/map.h"
#include <QList>
#include <QVector>
#include <QString>

class AStar
{

private:
    const Map& map;
    QPoint start;
    QPoint end;

    class MapNode {
        // cuz this is a private class, so I just make everything public
    public:
        enum class State {OPEN, CLOSE, NONE}; // node state
        int x;
        int y;
        int cost{-1};
        int gCost{-1};
        int hCost{-1};
        MapNode* parent{nullptr};
        State state;
        MapNode(int x, int y): x{x}, y{y} {
            state = State::NONE;
        }

        MapNode(int x, int y, int cost, MapNode* parent): x{x}, y{y}, cost{cost}, parent{parent} {
            state = State::NONE;
        }

        QPoint toQPoint() const {return QPoint{x, y};}

        QString toString() const {
            return QString{"Node at (%1, %2), state: %3"}.arg(QString::number(x)).arg(QString::number(y)).arg(QString{state == State::NONE? "NONE" : state == State::CLOSE? "CLOSE": "OPEN"});
        }

        ~MapNode() {}
    };

public:
    AStar() = delete;

    AStar(const Map& map);

    AStar(const AStar& pathingInstance);

    /**
     * @brief minCostNode Search the node which has the minimum cost in open list
     * @param list Open list to check
     * @return index of the node
     */
    int minCostNode(QList<MapNode*>& list) const;

    /**
     * @brief evaluateGCost calculate the G cost (Visiting Cost) of node
     * @param from Starting node / Parent
     * @param to The node that need to be calcuated G cost
     * @return G Cost
     */
    int evaluateGCost(const MapNode& from, const MapNode& to) const;

    /**
     * @brief evaluateHCost Calculate the H cost (cost from current node to end node) of node
     * @param current Current node
     * @return H Cost
     */
    int evaluateHCost(const MapNode& current) const;

    /**
     * @brief evaluateCost Calculate the overall cost of a node
     * @param from Starting node / Parent
     * @param to The node that need to be calcuated cost
     * @return Overall cost
     */
    int evaluateCost(MapNode& from, MapNode& to) const;

    /**
     * @brief initialState initialize map node visiting state
     * @param state Map Node list
     */
    void initialState(QVector<QVector<MapNode>>& mapNodeList) const;

    template<typename F>
    /**
     * @brief forEachNeighbor Iterator of available neighbor
     * @param node Node to get neighbors
     * @param stepValue How "heigh" can the target travels
     * @param process Process function for neighbors
     */
    void forEachNeighbor(const MapNode& node, int stepValue, F process) const;

    /**
     * @brief search Search the available pathing from start node to end node
     * @param start Starting Point, in GRID unit
     * @param end Ending point, in GRID unit
     * @param stepValue How "high" can the target travels
     * @return Pathing in QList format
     */
    QList<QPoint> search(QPoint start, QPoint end, int stepValue = 5);
};

#endif // PATHING_H
