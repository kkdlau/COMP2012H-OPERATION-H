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
#include "GameCharacter/enemy.h"
#include "ui_mapviewpage.h"

using namespace std;

MapViewPage::MapViewPage(const QString& mapImgPath,
                         const QString& mapConfigPath, int numMelee, int numRanged, int bulletSpeed, QWidget* parent)
	: QDialog(parent), ui(new Ui::MapViewPage) {
    this->numMelee = numMelee;
    this->numRanged = numRanged;
    this->bulletSpeed = bulletSpeed;
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowTitleHint);

	ui->setupUi(this);
	ui->gameCanvas->createMap(mapImgPath, mapConfigPath);

	characterController = new Character::Controller;
	cameraController = new Camera{ui->gameCanvas};

	initializeManager();
	characterManager->set_map(ui->gameCanvas->gameLayers()->mapLayer());
    mainCharacter = characterManager->generate_random_character();
	ui->gameCanvas->setMainCharacter(mainCharacter);
	mainCharacter->setGridPos(generateRandomMapPos());

	initializeItemFrame(mainCharacter);

    qDebug() << "Random Debuggin sentence";
    qDebug() << "Debuggin number of melee" << this->numMelee;
    qDebug() << "Debugging number of ranged" << this->numRanged;

    Map& map = *(ui->gameCanvas->gameLayers()->mapLayer());
    QPoint random_pos;
    // Putting melee weapons on the map : )
    for (int i =0; i < numMelee; i++) {
        random_pos = generateRandomMapPos();
        while(map[random_pos].isWeaponOnGround()) {
            random_pos = generateRandomMapPos();
        }
        putWeapon(weaponManager->GenerateRandomWeapon(QString("Melee")), random_pos.y(), random_pos.x());
    }

    // Putting ranged weapons on the map : )
    for (int i =0; i < numRanged; i++) {
        random_pos = generateRandomMapPos();
        while(map[random_pos].isWeaponOnGround()) {
            random_pos = generateRandomMapPos();
        }
        putWeapon(weaponManager->GenerateRandomWeapon(QString("Ranged")), random_pos.y(), random_pos.x());
    }

    // TODO: Set the bullet speed :(

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
        ui->generateEnemyButton->setDisabled(true);
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
    new_enemy->equipWeapon(weaponManager->GenerateRandomWeapon(QString("Ranged")));

	return new_enemy;
}

void MapViewPage::on_generateEnemyButton_clicked() {
    if (!mainCharacter->is_alive()) return;
	Enemy* enemy = generateEnemy();
	enemy->setGridPos(generateRandomMapPos());
}

void MapViewPage::setMapPath(QString inputPath) { mapPath = inputPath; }

QPoint MapViewPage::generateRandomMapPos() const {
	const unsigned width =
		unsigned(ui->gameCanvas->gameLayers()->mapLayer()->getWidth(
			Map::UNIT::GRID)) -
        2;
	const unsigned height =
		unsigned(ui->gameCanvas->gameLayers()->mapLayer()->getHeight(
			Map::UNIT::GRID)) -
        2;
    unsigned int x = QRandomGenerator::global()->bounded(2u, width);
    unsigned int y = QRandomGenerator::global()->bounded(2u, height);

	const Map& map = *(ui->gameCanvas->gameLayers()->mapLayer());
	while (map[y][x].getHeight() != 0) {
        x = QRandomGenerator::global()->bounded(2u, width);
        y = QRandomGenerator::global()->bounded(2u, height);
	}

	return QPoint{int(x), int(y)};
}

void MapViewPage::on_closeButton_clicked() { delete this; }

