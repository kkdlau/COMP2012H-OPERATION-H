#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"
#include "networkpage.h"
#include "Network/udp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    MapViewPage map_view_page;
    map_view_page.setModal(true);
    map_view_page.exec();
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
    network_page.setModal(true);
    network_page.exec();
}
