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
	QRectF screenSize = ui->gameCanvas->scene->sceneRect();
    playerItemFrame->setPos(screenSize.width() - 64, screenSize.height() -64);


    Enemy* test = characterManager->generate_random_enemy();
    test->setDestination(ui->gameCanvas->character);
	// test->equipWeapon(weaponManager->GenerateRandomWeapon());
    //	test->setPos(100, 100);
    ui->gameCanvas->scene->mapLayer()->addToGroup(test);
	ui->gameCanvas->scene->mapLayer()->addToGroup(ui->gameCanvas->character);

	ui->gameCanvas->cameraController->subscribe(ui->gameCanvas->character,
												&Character::isMoving);

	//	connect(this, &MapViewPage::keyPressEvent, &kbManager,
	//			&KeyboardManager::pressKey);
	//	connect(this, &MapViewPage::keyReleaseEvent, &kbManager,
	//			&KeyboardManager::releaseKey);
	//	connect(&kbManager, &KeyboardManager::comboPressed, this,
	//			&MapViewPage::comboHandler);
	//    connect(&kbManager, &KeyboardManager::emitKeyboardPressed, this,
	//            &MapViewPage::emitKeyboardPressed);

	Map* something = ui->gameCanvas->scene->mapLayer();

	GridInfo& idk = (*something)[3][3];
	idk.putWeapon(weaponManager->GenerateRandomWeapon());

	controller.control(ui->gameCanvas->character);
	timer.setInterval(50);
	timer.start();
	connect(&timer, &QTimer::timeout, this,
            [&]() {
                controller.updateKeyHoldingControl();
//ui->gameCanvas->character->moveTo(3, 3);
            });
}

void MapViewPage::keyPressEvent(QKeyEvent* e) {
	controller.setState(e->key(), true);
}

void MapViewPage::keyReleaseEvent(QKeyEvent* e) {
	controller.setState(e->key(), false);
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
