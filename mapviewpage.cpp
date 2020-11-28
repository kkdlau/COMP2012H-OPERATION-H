#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>
#include "Weapons/bullet.h"
#include "character.h"
#include "NewWeapon/rangedweapon.h"
#include "ui_mapviewpage.h"
#include "startpanel.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);

    ui->gameMap->character =
        new QGraphicsPixmapItem(QPixmap(":character_test"));
    //    ui->gameMap->character->setTransformOriginPoint(QPointF(16,16));
    ui->gameMap->character->setOffset(QPointF(-Map::GRID_SIZE_W / 2, -Map::GRID_SIZE_H / 2));
    ui->gameMap->scene->addItem(ui->gameMap->character);
    Character *sample = new Character();
    sample->setPos(100,100);
    sample->setPixmap(QPixmap(":character_test"));
    ui->gameMap->scene->addItem(sample);
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

    testWeapon = new RangedWeapon(10,500, 2000, 10);
    testWeapon->Equip(ui->gameMap->character, sample);
}

void MapViewPage::comboHandler(const QString& combo) {
	qDebug() << "combo detect: " << combo;
	if (combo == "A") {
		ui->gameMap->character->moveBy(-10, 0);
	} else if (combo == "S") {
		ui->gameMap->character->moveBy(0, 10);
	} else if (combo == "D") {
		ui->gameMap->character->moveBy(10, 0);
	} else if (combo == "W") {
		ui->gameMap->character->moveBy(0, -10);
	}
      else if(combo == "K")
    {
        testWeapon->Attack();
        qDebug()<<"FIREEE";
    }
        else if(combo == "M")
    {
        testWeapon->Attack();
        testWeapon->Attack();
    }
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
