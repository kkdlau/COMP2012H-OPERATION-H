#ifndef MAPVIEWPAGE_H
#define MAPVIEWPAGE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include "KeyBoardManager/keyboardmanager.h"

namespace Ui {
class MapViewPage;
}

class MapViewPage : public QDialog
{
    Q_OBJECT

public:
    explicit MapViewPage(QWidget *parent = nullptr);
    ~MapViewPage();

private:
    Ui::MapViewPage *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    KeyboardManager kbManager;

protected:
    void mouseMoveEvent(QMouseEvent*) override;
    void onMouseEvent(const QString& eName, const QPoint& p);
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
};

#endif // MAPVIEWPAGE_H
