#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"
#include "networkpage.h"
#include "Network/udp.h"
#include "remoteselector.h"
#include <QtBluetooth>

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

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

void MainWindow::on_pushButton_4_clicked()
{
    const QBluetoothAddress adapter = localAdapters.isEmpty() ?
                                           QBluetoothAddress() :
                                           localAdapters.at(0).address();
    RemoteSelector remote_selector(adapter);
    remote_selector.startDiscovery(QBluetoothUuid(serviceUuid));
    remote_selector.exec();



//    NetworkPage network_page;
//    network_page.setModal(true);
//    network_page.exec();
}
