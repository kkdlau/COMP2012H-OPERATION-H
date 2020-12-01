#include "itemframe.h"
#include "QBrush"

QGraphicsPixmapItem *ItemFrame::item = nullptr;

ItemFrame::ItemFrame()
{
    layout.setRect(0,0,16,16);
    layout.setBrush(QBrush(Qt::red));
    item = new QGraphicsPixmapItem();
    addToGroup(&layout);
    addToGroup(item);
}
