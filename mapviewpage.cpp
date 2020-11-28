#include "mapviewpage.h"

#include <QDebug>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QTimeLine>
#include <iostream>
#include "../character.h"

#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);

    ui->gameCanvas->character = new Character{5, ui->gameCanvas->map};
    //    ui->gameCanvas->character->setTransformOriginPoint(QPointF(16,16));
    //    ui->gameCanvas->character->setOffset(QPointF(-Map::GRID_SIZE_W / 2, -Map::GRID_SIZE_H / 2));
    ui->gameCanvas->scene->addItem(ui->gameCanvas->character);

	connect(this, &MapViewPage::keyPressEvent, &kbManager,
			&KeyboardManager::pressKey);
	connect(this, &MapViewPage::keyReleaseEvent, &kbManager,
			&KeyboardManager::releaseKey);
	connect(&kbManager, &KeyboardManager::comboPressed, this,
			&MapViewPage::comboHandler);

	this->kbManager.addListeningCombo("A")
		.addListeningCombo("S")
		.addListeningCombo("D")
		.addListeningCombo("W");
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
        ui->gameCanvas->character->moveBy(0, -10);
	}
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	//	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
