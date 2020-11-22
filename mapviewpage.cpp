#include "mapviewpage.h"

#include <QDebug>
#include <QPoint>
#include <iostream>

#include "ui_mapviewpage.h"

using namespace std;

void test() {
	qDebug() << "A and S are pressed"
			 << "\n";
}

MapViewPage::MapViewPage(QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage), kbManager(this) {
	ui->setupUi(this);
	scene = new QGraphicsScene(this);
	//    ui->gameMap->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//    ui->gameMap->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->gameMap->setScene(scene);

	QPixmap* pixmap = new QPixmap(":test_map.png");
	cout << "width: " << pixmap->size().width() << endl;
	scene->addPixmap(*pixmap);

	QBrush greenBrush(Qt::green);
	QBrush blueBrush(Qt::blue);
	QPen outlinePen(Qt::black);
	outlinePen.setWidth(2);

	rectangle = scene->addRect(0, 0, 32, 32, outlinePen, blueBrush);

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
		rectangle->setPos(rectangle->pos() + QPoint(-10, 0));
	} else if (combo == "S") {
		rectangle->setPos(rectangle->pos() + QPoint(0, 10));
	} else if (combo == "D") {
		rectangle->setPos(rectangle->pos() + QPoint(10, 0));
	} else if (combo == "W") {
		rectangle->setPos(rectangle->pos() + QPoint(0, -10));
	}
	scene->setSceneRect(QRectF(0, 0, 320, 320));
	qDebug() << rectangle->pos();
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
	qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage() { delete ui; }
