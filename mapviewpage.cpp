#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>
#include <QDialogButtonBox>
#include "UI/itemframe.h"
#include "enemy.h"
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
    : QDialog(parent), ui(new Ui::MapViewPage) {
	ui->setupUi(this);

    characterController = new Character::Controller;
    cameraController = new Camera{ui->gameCanvas};

	initializeManager();
	characterManager->set_map(ui->gameCanvas->scene->mapLayer());
    Character* mainCharacter = ui->gameCanvas->character = characterManager->generate_random_character();

    initializeItemFrame(mainCharacter);

    Enemy* test = characterManager->generate_random_enemy();
    test->equipWeapon(weaponManager->GenerateRandomWeapon());
    ui->gameCanvas->scene->mapLayer()->addToGroup(test);
	ui->gameCanvas->scene->mapLayer()->addToGroup(ui->gameCanvas->character);

    putWeapon(weaponManager->GenerateRandomWeapon(), 8, 2);

    characterController->control(ui->gameCanvas->character);
	timer.setInterval(50);
	timer.start();
	connect(&timer, &QTimer::timeout, this,
            [&]() {
                characterController->updateKeyHoldingControl();
            });

    connect(ui->gameCanvas->character, &Character::deadSignal, this, [&]() {
        characterController->unControl();
    });

}

void MapViewPage::putWeapon(Weapon* weapon, int x, int y) {
    Map& currentMap = *(ui->gameCanvas->scene->mapLayer());
    currentMap[y][x].putWeapon(weapon);

}

void MapViewPage::initializeItemFrame(Character* c) {
    const QPoint BOTTOM_RIGHT_CORNER{250, 250};

    ItemFrame* itemFrame = ui->gameCanvas->scene->getItemFrame();
    itemFrame->characterSingalSetup(ui->gameCanvas->character);
    itemFrame->setPos(BOTTOM_RIGHT_CORNER);
}

void MapViewPage::keyPressEvent(QKeyEvent* e) {
    characterController->setState(e->key(), Character::Controller::PRESSED);
}

void MapViewPage::keyReleaseEvent(QKeyEvent* e) {
    characterController->setState(e->key(), Character::Controller::RELEASED);
}

CharacterManager* MapViewPage::get_character_manager() {
    return characterManager;
}

MapViewPage::~MapViewPage() {
	delete ui;
	delete characterManager;
	delete weaponManager;
    delete characterController;
    delete cameraController;
}

void MapViewPage::initializeManager() {
	weaponManager = WeaponManager::getInstance();
	characterManager = CharacterManager::getInstance();
}

void MapViewPage::on_generateEnemyButton_clicked()
{
    Enemy* new_enemy = characterManager->generate_random_enemy();
}

void MapViewPage::setMapPath(QString inputPath) {
    mapPath = inputPath;
}


void MapViewPage::on_closeButton_clicked()
{
    delete this;
}
