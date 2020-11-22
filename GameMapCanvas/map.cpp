#include "map.h"

#include <QDebug>
#include <QList>
#include <QFile>

const unsigned short Map::GRID_SIZE_W = 32;
const unsigned short Map::GRID_SIZE_H = 32;

Map::Map(QObject* parent, QString resourceName, QString mapConfigFilePath) : QGraphicsScene{parent} {
	mapImg = new QPixmap(resourceName);
	addPixmap(*mapImg);
    QFile f{mapConfigFilePath};
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray first_line = f.readLine();
    QList<QByteArray> list =  first_line.split(' ');
    bool success;
    int width = list[0].toInt(&success, 10);
    if (success) qDebug() << "width: " << width;
    int height = list[0].toInt(&success, 10);
    if (success) qDebug() << "height: " << height;

    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        list = line.split(' ');
        int pos_x = list[0].toInt(&success, 10);
        int pos_y = list[1].toInt(&success, 10);
        float height = list[2].toFloat(&success);

        QColor clr = Qt::green;
        clr.setAlphaF(height/ 10.0);
        QBrush tmpBrush{clr};
        QPen tmpPen;
        tmpPen.setColor(Qt::blue);
        tmpPen.setWidth(2);

        addRect(pos_x*32, pos_y*32, 32, 32, tmpPen, tmpBrush);
    }
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
	QGraphicsScene::mouseMoveEvent(e);
	cursorPos = e->scenePos();
}

const QPointF& Map::get_cursor_on_map() const { return cursorPos; }

Map::~Map() { delete mapImg; }
