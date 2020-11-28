#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mapviewpage.h"
#include "startpanel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsView *sample = new QGraphicsView(ui->container);
    StartPanel *vara = new StartPanel();
    sample->setScene(vara->getScene());
    sample->show();
    sample->fitInView(vara->getScene()->sceneRect());
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
