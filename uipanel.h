#ifndef UIPANEL_H
#define UIPANEL_H
#include "QGraphicsPixmapItem"
#include "QGraphicsView"

#include <QObject>

class UIPanel : public QGraphicsView
{
    Q_OBJECT
public:
    UIPanel(QWidget *something);
};

#endif // UIPANEL_H
