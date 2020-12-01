#ifndef ITEMFRAME_H
#define ITEMFRAME_H
#include "QGraphicsItemGroup"

class ItemFrame : public QObject, public QGraphicsItemGroup
{
public:
    ItemFrame();
    static QGraphicsPixmapItem *item;
private:
    QGraphicsRectItem layout;

};
#endif // ITEMFRAME_H
