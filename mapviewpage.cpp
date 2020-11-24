#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>
#include "Weapons/bullet.h"

#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);

	ui->gameMap->character =
		new QGraphicsPixmapItem(QPixmap(":character_test"));
	//    ui->gameMap->character->setTransformOriginPoint(QPointF(16,16));
    ui->gameMap->character->setOffset(QPointF(-Map::GRID_SIZE_W / 2, -Map::GRID_SIZE_H / 2));
	ui->gameMap->scene->addItem(ui->gameMap->character);

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
        .addListeningCombo("K");
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
        qDebug()<<"SFJHSFKJHSFKJ";
        Bullet *test = new Bullet(1, 45, 1, ui->gameMap->character->x(), ui->gameMap->character->y());
        ui->gameMap->scene->addItem(test);


    }
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
