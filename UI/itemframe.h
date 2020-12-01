#ifndef ITEMFRAME_H
#define ITEMFRAME_H
#include "QGraphicsItemGroup"
#include <QGraphicsProxyWidget>
#include <QLabel>

class ItemFrame : public QObject, public QGraphicsItemGroup
{
public:
    ItemFrame();
    ~ItemFrame();
    void ChangeWeaponPicture(QPixmap picture);
    void ChangeText(QString data);
protected:
    QGraphicsRectItem *layout;
    QGraphicsPixmapItem *weaponImage;
    QGraphicsProxyWidget *labelProxy;
    QLabel *weaponStat;

};
#endif // ITEMFRAME_H
