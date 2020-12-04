#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Network/client.h"
#include "Network/server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Map1_clicked();

    void on_pushButton_Map2_clicked();

    void on_pushButton_Map3_clicked();

    void on_pushButton_GameStart_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    MapViewPage* map_view_page;
    QString selectedMapPath{":map_2.png"};
    QString selectedConfigPath{":map_2.txt"};
    int numMelee{1};
    int numRanged{1};
    int bulletSpeed{1};
};
#endif // MAINWINDOW_H
