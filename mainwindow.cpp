#include <QGraphicsItem>
#include "mainwindow.h"
#include "mapviewpage.h"
#include "networkpage.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) {
{
		setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint |
					   Qt::WindowTitleHint);
		ui->setupUi(this);
		ui->label->setPixmap(
			QPixmap(":game_logo.png")
                .scaled(ui->label->width(), ui->label->height()));
        selectedMapPath = ":map1.png";
        selectedConfigPath = ":map1.txt";
	}
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_Map1_clicked() {
	qDebug() << "Map1 Pressed";
	selectedMapPath = ":map1.png";
	selectedConfigPath = ":map1.txt";
}

void MainWindow::on_pushButton_Map2_clicked() {
	qDebug() << "Map2 Pressed";
	selectedMapPath = ":map2.png";
	selectedConfigPath = ":map2.txt";
}

void MainWindow::on_pushButton_Map3_clicked() {
	qDebug() << "Map3 Pressed";
	selectedMapPath = ":map3.png";
	selectedConfigPath = ":map3.txt";
}

void MainWindow::on_pushButton_GameStart_clicked() {
	map_view_page = new MapViewPage(selectedMapPath, selectedConfigPath);
	map_view_page->setMapPath(selectedMapPath);
	map_view_page->setModal(true);
	qDebug() << "Current Map Path: " << selectedMapPath;
	map_view_page->exec();
}

void MainWindow::on_pushButton_4_clicked() {
	NetworkPage network_page;
	network_page.set_game_page(map_view_page);
	network_page.setModal(true);
	network_page.exec();
}

void MainWindow::on_pushButton_clicked()
{
    delete this;
    exit(0);
}
