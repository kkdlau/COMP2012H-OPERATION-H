#ifndef CAMERA_H
#define CAMERA_H
#include "GameCharacter/character.h"
#include <QSize>
#include <QMetaObject>
#include <QGraphicsView>

class GameMapCanvas;

class Camera: public QObject
{
    Q_OBJECT
private:
    GameMapCanvas* canvas{nullptr}; // internal variable for update canvas rect
    int windowWidth; // canvas width
    int windowHeight; // canvas height
    QMetaObject::Connection cameraMoveConnection;
    QMetaObject::Connection canvasSizeChangeConnection;

    /**
     * @brief updateVerticalFocus Update Canvas Viewport according to the vertical coordinate
     * @param v vertical coordinate
     */
    void updateVerticalFocus(qreal v);

    /**
     * @brief updateHorizontalFocus Update Canvas Viewport according to the horizontal coordinate
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
     * @brief registerCanvas Register canvas to camera. Camera will take the control of canvas's viewport.
     * @param canvas canvas to register
     */
    void registerCanvas(GameMapCanvas* canvas);



    /**
     * @brief subscribe Make the camera subscribe to the Character position singal. When singaled, this will tell the Camera to readjust to Character's current position.
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

    ~Camera();
};

#include "gamemapcanvas.h"

#endif // CAMERA_H
