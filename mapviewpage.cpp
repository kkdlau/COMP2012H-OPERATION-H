#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>

#include "UI/itemframe.h"
#include "enemy.h"
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);
	ui->gameCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	initializeManager();
	characterManager->set_map(ui->gameCanvas->scene->mapLayer());
	ui->gameCanvas->character = characterManager->generate_random_character();
	ItemFrame* playerItemFrame = ui->gameCanvas->scene->getItemFrame();
	playerItemFrame->characterSingalSetup(ui->gameCanvas->character);
    playerItemFrame->setPos(250,250);
    Enemy* test = characterManager->generate_random_enemy();
    //test->setDestination(ui->gameCanvas->character);
    test->equipWeapon(weaponManager->GenerateRandomWeapon());
    //	test->setPos(100, 100);
    ui->gameCanvas->scene->mapLayer()->addToGroup(test);
	ui->gameCanvas->scene->mapLayer()->addToGroup(ui->gameCanvas->character);

	ui->gameCanvas->cameraController->subscribe(ui->gameCanvas->character,
												&Character::isMoving);
	Map* something = ui->gameCanvas->scene->mapLayer();

    GridInfo& idk = (*something)[8][2];
	idk.putWeapon(weaponManager->GenerateRandomWeapon());

	controller.control(ui->gameCanvas->character);
	timer.setInterval(50);
	timer.start();
	connect(&timer, &QTimer::timeout, this,
            [&]() {
                controller.updateKeyHoldingControl();
//ui->gameCanvas->character->moveTo(3, 3);
            });

    connect(ui->gameCanvas->character, &Character::deadSignal, this, [&]() {
       controller.unControl();
    });
}

void MapViewPage::keyPressEvent(QKeyEvent* e) {
	controller.setState(e->key(), true);
}

void MapViewPage::keyReleaseEvent(QKeyEvent* e) {
	controller.setState(e->key(), false);
}

CharacterManager* MapViewPage::get_character_manager() {
    return characterManager;
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() {
	delete ui;
	delete characterManager;
	delete weaponManager;
}

void MapViewPage::initializeManager() {
	weaponManager = WeaponManager::getInstance();
	characterManager = CharacterManager::getInstance();
}
