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
    kbManager()
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    QPixmap* pixmap = new QPixmap(":test_map.png");
    cout << "width: " << pixmap->size().width() << endl;
    scene->addPixmap(*pixmap);

    this->kbManager.addCombo("A", [&]() {
        ui->graphicsView->scroll(10, 0);
    });

    this->kbManager.addCombo("S", [&]() {
        ui->graphicsView->scroll(0, -10);
    });

    this->kbManager.addCombo("D", [&]() {
        ui->graphicsView->scroll(-10, 0);
    });

    this->kbManager.addCombo("W", [&]() {
        ui->graphicsView->scroll(0, 10);
    });
}

void MapViewPage::mouseMoveEvent(QMouseEvent* e) {
    qDebug() << e->x() << ", " << e->y() << "\n";
}


void MapViewPage::keyPressEvent(QKeyEvent* k) {
    qDebug() << k->key() << "\n";
    kbManager.pressKey(k->key());
}

void MapViewPage::keyReleaseEvent(QKeyEvent* k) {
    kbManager.releaseKey(k->key());
}

MapViewPage::~MapViewPage()
{
    delete ui;
}
