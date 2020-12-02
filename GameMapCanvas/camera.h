#ifndef CAMERA_H
#define CAMERA_H
#include "../character.h"
#include <QSize>
#include <QMetaObject>
#include <QGraphicsView>

class GameMapCanvas;

class Camera: public QObject
{
    Q_OBJECT
private:
    GameMapCanvas* canvas{nullptr};
    int windowWidth;
    int windowHeight;
    QMetaObject::Connection cameraMoveConnection;
    QMetaObject::Connection canvasSizeChangeConnection;

    void updateVerticalFocus(qreal v);
    void updateHorizontalFocus(qreal h);

    void unsubscribeCanvasSizeEvent();

public:
    Camera() = default;
    Camera(GameMapCanvas* canvas, Character* c = nullptr);

    void registerCanvas(GameMapCanvas* canvas);

    template<typename funcOwner, typename functionPointer>
    void subscribe(funcOwner owner, functionPointer funcs);

    void unsubscribe();

    ~Camera();

private slots:
    void updateFocus(QPointF p);
    void updateCanvasSize(QSizeF size);
};

#include "gamemapcanvas.h"

#endif // CAMERA_H
