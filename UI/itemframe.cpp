#include "itemframe.h"
#include "QBrush"

ItemFrame::ItemFrame()
{
    layout = new QGraphicsRectItem();
    layout->setRect(0,0,16,16);
    layout->setBrush(QBrush(Qt::red));
    labelProxy = new QGraphicsProxyWidget();
    weaponStat = new QLabel();
    weaponImage = new QGraphicsPixmapItem();
    labelProxy->setWidget(weaponStat);
    weaponStat->setText("-/-");
    labelProxy->setPos(0, 10);
    addToGroup(layout);
    addToGroup(weaponImage);
    addToGroup(labelProxy);
}

ItemFrame::~ItemFrame()
{
    delete layout;
    delete weaponImage;
    delete labelProxy;
}

void ItemFrame::ChangeText(QString data)
{
    weaponStat->setText(data);
}

void ItemFrame::ChangeWeaponPicture(QPixmap picture)
{
    weaponImage->setPixmap(picture);
}
