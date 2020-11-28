#ifndef STARTPANEL_H
#define STARTPANEL_H
#include "uipanel.h"
#include "QPushButton"
#include "qgraphicsproxywidget.h"
#include "qgraphicsgridlayout.h"
#include "qgraphicsscene.h"


class StartPanel : public QGraphicsScene
{
public:
    StartPanel();
    QGraphicsScene *getScene();
    QPushButton *getButtonStart();
    QPushButton *getButtonQuit();
    void initializeButton(QPushButton *button);
    void testFunc();
private:
    QPushButton startButton;
    QPushButton endButton;
    QGraphicsPixmapItem sampleBackground;
};

#endif // STARTPANEL_H
