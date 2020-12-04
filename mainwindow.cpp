#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"
#include "networkpage.h"
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":game_logo.png").scaled(ui->label->width(),ui->label->height()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Map1_clicked()
{
    qDebug() << "Map1 Pressed";
    selectedMapPath = ":test_map.png";
}

void MainWindow::on_pushButton_Map2_clicked()
{
    qDebug() << "Map2 Pressed";
    selectedMapPath = ":map_2.png";
}

void MainWindow::on_pushButton_Map3_clicked()
{
    qDebug() << "Map3 Pressed";
    selectedMapPath = ":map3.jpeg";
}


void MainWindow::on_pushButton_GameStart_clicked()
{
    map_view_page = new MapViewPage();
    map_view_page->setMapPath(selectedMapPath);
    map_view_page->setModal(true);
    qDebug() << "Current Map Path: " << selectedMapPath;
    map_view_page->exec();
}



void MainWindow::on_pushButton_4_clicked()
{
    NetworkPage network_page;
    network_page.set_game_page(map_view_page);
    network_page.setModal(true);
    network_page.exec();
}
