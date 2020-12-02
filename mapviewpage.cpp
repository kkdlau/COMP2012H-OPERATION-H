#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>

#include "UI/itemframe.h"
#include "character.h"
#include "enemy.h"
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);
	ui->gameCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	ui->gameCanvas->character = new Character{5, ui->gameCanvas->map};
	ItemFrame* playerItemFrame = new ItemFrame();
	ui->gameCanvas->character->weaponUI = playerItemFrame;
	ui->gameCanvas->scene->addItem(playerItemFrame);
	playerItemFrame->setPos(200, 200);

	//    Enemy *test = new Enemy{ui->gameCanvas->map, 100,
	//    ui->gameCanvas->character}; test->setPos(300, 50);
	//    ui->gameCanvas->scene->addItem(test);

	ui->gameCanvas->map->mapLayer()->addToGroup(ui->gameCanvas->character);

	ui->gameCanvas->cameraController->subscribe(ui->gameCanvas->character,
												&Character::isMoving);

	connect(this, &MapViewPage::keyPressEvent, &kbManager,
			&KeyboardManager::pressKey);
	connect(this, &MapViewPage::keyReleaseEvent, &kbManager,
			&KeyboardManager::releaseKey);
	connect(&kbManager, &KeyboardManager::comboPressed, this,
			&MapViewPage::comboHandler);

	this->kbManager.addListeningCombo("A")
		.addListeningCombo("S")
		.addListeningCombo("D")
		.addListeningCombo("W")
		.addListeningCombo("K")
		.addListeningCombo("M");

	weaponManager = WeaponManager::getInstance();
	//    weaponManager->setPos(200,200);
	//    ui->gameCanvas->scene->addItem(weaponManager);
	Map* something = ui->gameCanvas->map;

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
