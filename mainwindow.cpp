#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"

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
