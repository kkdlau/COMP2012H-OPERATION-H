#include "mapviewpage.h"

#include <QDebug>
#include <QPoint>
#include <iostream>
#include <QTimeLine>
#include <QPointF>
#include <QGraphicsItemAnimation>
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);
    ui->gameMap->scene = new QGraphicsScene(this);
    ui->gameMap->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameMap->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameMap->setScene(ui->gameMap->scene);

    ui->gameMap->character = new QGraphicsPixmapItem(QPixmap(":character_test"));
    ui->gameMap->character->setTransformOriginPoint(QPointF(16,16));

	QPixmap* pixmap = new QPixmap(":test_map.png");

    ui->gameMap->scene->addPixmap(*pixmap);
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
		.addListeningCombo("W");
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
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
