#include "mapviewpage.h"
#include "ui_mapviewpage.h"
#include <QDebug>
#include <iostream>

using namespace std;

void test() {
    qDebug() << "A and S are pressed" << "\n";
}

MapViewPage::MapViewPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapViewPage),
    kbManager(this)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    QPixmap* pixmap = new QPixmap(":test_map.png");
    cout << "width: " << pixmap->size().width() << endl;
    scene->addPixmap(*pixmap);

    connect(this, &MapViewPage::keyPressEvent, &kbManager, &KeyboardManager::pressKey);
    connect(this, &MapViewPage::keyReleaseEvent, &kbManager, &KeyboardManager::releaseKey);
    connect(&kbManager, &KeyboardManager::comboPressed, this, &MapViewPage::comboHandler);

    this->kbManager.addListeningCombo("A")
            .addListeningCombo("S")
            .addListeningCombo("D")
            .addListeningCombo("W");
}

void MapViewPage::comboHandler(const QString& combo) {
    qDebug() << "combo detect: " << combo;
    if (combo == "A") {
        ui->graphicsView->scroll(10, 0);
    } else if (combo == "S") {
        ui->graphicsView->scroll(0, -10);
    } else if (combo == "D") {
        ui->graphicsView->scroll(-10, 0);
    } else if (combo == "W") {
        ui->graphicsView->scroll(0, 10);
    }
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
    qDebug() << e->x() << ", " << e->y() << "\n";
}

MapViewPage::~MapViewPage()
{
    delete ui;
}
