#ifndef MAPVIEWPAGE_H
#define MAPVIEWPAGE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "NewWeapon/weaponmanager.h"
#include "GameCharacter/charactermanager.h"
#include <QTimer>
#include "GameScene/camera.h"

namespace Ui {
class MapViewPage;
}

class MapViewPage : public QDialog
{
    Q_OBJECT

public:
    explicit MapViewPage(const QString& mapImgPath, const QString& mapConfigPath, int numMelee, int numRanged, int bulletSpeed, QWidget *parent = nullptr);
    ~MapViewPage();
    void setMapPath(QString inputPath);

private:

    Ui::MapViewPage *ui;
    int numMelee;
    int numRanged;
    int bulletSpeed;

    QTimer timer;
    Character::Controller controller;
    QString mapPath;

    Character* mainCharacter;
    Camera* cameraController;
    Character::Controller* characterController;

    /**
     * @brief initializeManager initialize the managers;
     */
    void initializeManager();
    CharacterManager* characterManager;
    WeaponManager* weaponManager;

    /**
     * @brief initializeItemFrame Intialize the item frame
     * @param c character to listen
     */
    void initializeItemFrame(Character* c);

    /**
     * @brief putWeapon Put the weapon on the ground
     * @param weapon weapon to put
     * @param x Grid X coordinate
     * @param y Grid Y coordinate
     */
    void putWeapon(Weapon* weapon, int x, int y);

    /**
     * @brief generateEnemy generate the enemy which chases the character
     */
    Enemy* generateEnemy() const;

    QPoint generateRandomMapPos() const;

public:
    CharacterManager* get_character_manager();
    void onMouseEvent(const QString& eName, const QPoint& p);
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
signals:
    void emitKeyboardPressed();

private slots:
    void on_generateEnemyButton_clicked();
    void on_closeButton_clicked();
};

#endif // MAPVIEWPAGE_H
