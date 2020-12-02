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
    weaponManager = WeaponManager::getInstance();
    characterManager = CharacterManager::get_instance();
    characterManager->set_map(ui->gameCanvas->scene->mapLayer());
    ui->gameCanvas->character = characterManager->generate_random_character();
//	ItemFrame* playerItemFrame = new ItemFrame();
//	ui->gameCanvas->character->weaponUI = playerItemFrame;
//	ui->gameCanvas->scene->addItem(playerItemFrame);
//  QRectF screenSize= ui->gameCanvas->scene->sceneRect();
//  playerItemFrame->setPos(screenSize.width() - 64, screenSize.height() - 64);
    Enemy *test = characterManager->generate_random_enemy();
    //test->setDestination(ui->gameCanvas->character);
    test->equipWeapon(weaponManager->GenerateRandomWeapon());
    test->setPos(100, 100);
    ui->gameCanvas->scene->mapLayer()->addToGroup(test);
    ui->gameCanvas->scene->mapLayer()->addToGroup(ui->gameCanvas->character);

	ui->gameCanvas->cameraController->subscribe(ui->gameCanvas->character,
												&Character::isMoving);

	connect(this, &MapViewPage::keyPressEvent, &kbManager,
			&KeyboardManager::pressKey);
	connect(this, &MapViewPage::keyReleaseEvent, &kbManager,
			&KeyboardManager::releaseKey);
	connect(&kbManager, &KeyboardManager::comboPressed, this,
			&MapViewPage::comboHandler);
    connect(&kbManager, &KeyboardManager::emitKeyboardPressed, this,
            &MapViewPage::emitKeyboardPressed);

	this->kbManager.addListeningCombo("A")
		.addListeningCombo("S")
		.addListeningCombo("D")
		.addListeningCombo("W")
		.addListeningCombo("K")
		.addListeningCombo("M");


	//    weaponManager->setPos(200,200);
	//    ui->gameCanvas->scene->addItem(weaponManager);
    Map* something = ui->gameCanvas->scene->mapLayer();

	GridInfo& idk = (*something)[0][0];
	idk.putWeapon(weaponManager->GenerateRandomWeapon());
}

void MapViewPage::comboHandler(const QString& combo) {
	qDebug() << "combo detect: " << combo;
	if (combo == "A") {
		ui->gameCanvas->character->moveBy(-10, 0);
	} else if (combo == "S") {
		ui->gameCanvas->character->moveBy(0, 10);
	} else if (combo == "D") {
		ui->gameCanvas->character->moveBy(10, 0);
	} else if (combo == "W") {
		ui->gameCanvas->character->moveBy(0, -5);
	} else if (combo == "K") {
		ui->gameCanvas->character->pickWeapon();
	} else if (combo == "M") {
		ui->gameCanvas->character->shoot();
	}
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
