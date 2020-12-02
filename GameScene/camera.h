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
    GameMapCanvas* canvas{nullptr}; // internal variable for update canvas rect
    int windowWidth;
    int windowHeight;
    QMetaObject::Connection cameraMoveConnection;
    QMetaObject::Connection canvasSizeChangeConnection;

    /**
     * @brief updateVerticalFocus Update Canvas Viewport according to vertical coordinate
     * @param v vertical coordinate
     */
    void updateVerticalFocus(qreal v);

    /**
     * @brief updateHorizontalFocus Update Canvas Viewport according to horizontal coordinate
     * @param h horizontal coordinate
     */
    void updateHorizontalFocus(qreal h);

    /**
     * @brief unsubscribeCanvasSizeEvent Unsubscribe canvas resize event. It will be called when registering canvas to camera.
     */
    void unsubscribeCanvasSizeEvent();

public:
    Camera() = default;
    Camera(GameMapCanvas* canvas, Character* c = nullptr);

    /**
     * @brief registerCanvas Register canvas to camera. Camera will take the control of cnavas's viewport.
     * @param canvas canvas to register
     */
    void registerCanvas(GameMapCanvas* canvas);



    /**
     * @brief subscribe Make camera subscribes the position changes singal. The canvas's viewport changes based on this singal also.
     * Please notes that the singal should **emit QPointF singal**.
     *
     * @param owner Signal owner
     * @param funcs Signal function
     */
    template<typename funcOwner, typename functionPointer>
    void subscribe(funcOwner owner, functionPointer funcs);

    /**
     * @brief unsubscribe Unsubscribe registered singal. Do nothing if no signal is subscribed.
     */
    void unsubscribe();

    ~Camera();

private slots:
    /**
     * @brief updateFocus Update camera and corresponding viewport by the given point.
     * @param p Point
     */
    void updateFocus(QPointF p);

    /**
     * @brief updateCanvasSize Update viewport size.
     * @param size The viewport size.
     */
    void updateCanvasSize(QSizeF size);
};

#include "gamemapcanvas.h"

#endif // CAMERA_H
