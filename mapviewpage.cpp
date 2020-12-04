#include "mapviewpage.h"

#include <QDebug>
#include <QDialogButtonBox>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include <QPointF>
#include <QRandomGenerator>
#include <QTimeLine>
#include <iostream>

#include "UI/itemframe.h"
#include "enemy.h"
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(const QString& mapImgPath,
						 const QString& mapConfigPath, QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage) {
	ui->setupUi(this);
	ui->gameCanvas->createMap(mapImgPath, mapConfigPath);

	characterController = new Character::Controller;
	cameraController = new Camera{ui->gameCanvas};

	initializeManager();
	characterManager->set_map(ui->gameCanvas->gameLayers()->mapLayer());
	Character* mainCharacter = characterManager->generate_random_character();
	ui->gameCanvas->setMainCharacter(mainCharacter);
	mainCharacter->setGridPos(generateRandomMapPos());

	initializeItemFrame(mainCharacter);

	Enemy* test = generateEnemy();
	test->setGridPos(generateRandomMapPos());

	putWeapon(weaponManager->GenerateRandomWeapon(), 8, 2);

	cameraController->subscribe(mainCharacter, &Character::isMoving);

	cameraController->updateFocus(mainCharacter->pos());

	characterController->control(mainCharacter);

	timer.setInterval(50);
	timer.start();
	connect(&timer, &QTimer::timeout, this,
			[&]() { characterController->updateKeyHoldingControl(); });

	connect(mainCharacter, &Character::deadSignal, this, [&]() {
		characterController->unControl();
		cameraController->unsubscribe();
	});
}

void MapViewPage::putWeapon(Weapon* weapon, int x, int y) {
	Map& currentMap = *(ui->gameCanvas->gameLayers()->mapLayer());
	currentMap[y][x].putWeapon(weapon);
}

void MapViewPage::initializeItemFrame(Character* c) {
	const QPoint BOTTOM_RIGHT_CORNER{250, 250};

	ItemFrame* itemFrame = ui->gameCanvas->gameLayers()->getItemFrame();
	itemFrame->characterSingalSetup(c);
	itemFrame->setPos(BOTTOM_RIGHT_CORNER);
}

void MapViewPage::keyPressEvent(QKeyEvent* e) {
	characterController->setState(e->key(), Character::Controller::PRESSED);
}

void MapViewPage::keyReleaseEvent(QKeyEvent* e) {
	characterController->setState(e->key(), Character::Controller::RELEASED);
}

CharacterManager* MapViewPage::get_character_manager() {
	return characterManager;
}

MapViewPage::~MapViewPage() {
	delete ui;
	delete characterManager;
	delete weaponManager;
	delete characterController;
	delete cameraController;
}

void MapViewPage::initializeManager() {
	weaponManager = WeaponManager::getInstance();
	characterManager = CharacterManager::getInstance();
}

Enemy* MapViewPage::generateEnemy() const {
	Enemy* new_enemy = characterManager->generate_random_enemy();
	new_enemy->equipWeapon(weaponManager->GenerateRandomWeapon());

	return new_enemy;
}

void MapViewPage::on_generateEnemyButton_clicked() {
	Enemy* enemy = generateEnemy();
	enemy->setGridPos(generateRandomMapPos());
}

void MapViewPage::setMapPath(QString inputPath) { mapPath = inputPath; }

QPoint MapViewPage::generateRandomMapPos() const {
	const unsigned width =
		unsigned(ui->gameCanvas->scene->mapLayer()->getWidth(Map::UNIT::GRID)) -
		1;
	const unsigned height =
		unsigned(
			ui->gameCanvas->scene->mapLayer()->getHeight(Map::UNIT::GRID)) -
		1;
	unsigned int x = QRandomGenerator::global()->bounded(0u, width);
	unsigned int y = QRandomGenerator::global()->bounded(0u, height);

	const Map& map = *(ui->gameCanvas->gameLayers()->mapLayer());
	while (map[y][x].getHeight() != 0) {
		x = QRandomGenerator::global()->bounded(0u, width);
		y = QRandomGenerator::global()->bounded(0u, height);
	}

	return QPoint{int(x), int(y)};
}

void MapViewPage::on_closeButton_clicked() { delete this; }
