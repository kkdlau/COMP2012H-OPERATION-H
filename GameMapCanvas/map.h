#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QString>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>

class Map: public QGraphicsScene {
private:
    QString mapName;
    QPixmap* mapImg;
    QPointF cursorPos;
public:
    Map(QObject *parent, QString resourceName);

    void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;

    const QPointF& get_cursor_on_map() const;
    ~Map();
};

#endif // MAP_H
