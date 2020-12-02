#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>
#include "character.h"
#include "enemy.h"

#include "ui_mapviewpage.h"
#include "UI/itemframe.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);
    ui->gameCanvas->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//    ui->gameCanvas->resize(320, 320);
//    ui->gameCanvas->fitInView(ui->gameCanvas->sceneRect(), Qt::KeepAspectRatio);

    ui->gameCanvas->character = new Character{5, ui->gameCanvas->map};
    Character *test = new Character{5, ui->gameCanvas->map};
    test->setPos(200, 0);
//    ui->gameCanvas->scene->addItem(test);
    //    ui->gameCanvas->character->setTransformOriginPoint(QPointF(16,16));
    //    ui->gameCanvas->character->setOffset(QPointF(-Map::GRID_SIZE_W / 2, -Map::GRID_SIZE_H / 2));
    ui->gameCanvas->scene->addItem(ui->gameCanvas->character);

    ui->gameCanvas->cameraController->subscribe(ui->gameCanvas->character, &Character::isMoving);


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

//    weaponManager = WeaponManager::getInstance();
//    MeleeWeapon *test1 = new MeleeWeapon(0, 50, 500);
//    RangedWeapon *test2 = new RangedWeapon(0, 500, 500, 10);
//    test1->setPos(100,250);
//    test2->setPos(150, 150);
//    ui->gameCanvas->scene->addItem(test1);
//    ui->gameCanvas->scene->addItem(test2);
//    weaponManager->AddWeapon(test1);
//    weaponManager->AddWeapon(test2);
//    ui->gameCanvas->scene->addItem(weaponManager->GenerateRandomWeapon());
//    ItemFrame *uiWeapon = new ItemFrame();
//    ui->gameCanvas->scene->addItem(uiWeapon);
//    uiWeapon->setPos(250,250);

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
	}
      else if(combo == "K")
    {
        ui->gameCanvas->character->EquipWeapon();
    }
      else if(combo == "M")
    {
        ui->gameCanvas->character->shoot();
    }
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
