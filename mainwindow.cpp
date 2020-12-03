#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"
#include "networkpage.h"
#include "Network/udp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , map_view_page(new MapViewPage)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Map1_clicked()
{
    qDebug() << "I want to quit U";
}

void MainWindow::on_pushButton_Map2_clicked()
{
    qDebug() << "I want to jump mushroom";
}

void MainWindow::on_pushButton_Map3_clicked()
{
    qDebug() << "But before all those I need to revise, fml";
}


void MainWindow::on_pushButton_GameStart_clicked()
{
    map_view_page->setModal(true);
    map_view_page->exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    UDP its_a_me;
    QString raw_message("Hello");
    its_a_me.say_hello_in_udp(raw_message);
}

void MainWindow::on_pushButton_3_clicked()
{
    UDP its_a_you;
    its_a_you.read_from_udp();
}


void MainWindow::on_pushButton_4_clicked()
{
    NetworkPage network_page;
    network_page.set_game_page(map_view_page);
    network_page.setModal(true);
    network_page.exec();
}
