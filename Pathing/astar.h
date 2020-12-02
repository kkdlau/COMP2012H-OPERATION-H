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
    public:
        enum class State {OPEN, CLOSE, NONE};
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

    int minCostNode(QList<MapNode*>& list) const;

    int evaluateGCost(const MapNode& from, const MapNode& to) const;

    int evaluateHCost(const MapNode& current) const;

    int evaluateCost(MapNode& from, MapNode& to, QPoint end) const;

    void initialState(QVector<QVector<MapNode>>& state) const;

    template<typename F>
    void forEachNeighbor(const MapNode& node, F process) const;

    QList<QPoint> search(QPoint start, QPoint end);
};

#endif // PATHING_H
