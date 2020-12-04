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
    /**
     * @brief on_pushButton_clicked slots for clicking button events
     */
    void on_pushButton_Map1_clicked();

    void on_pushButton_Map2_clicked();

    void on_pushButton_Map3_clicked();

    void on_pushButton_GameStart_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    MapViewPage* map_view_page;
    /**
     * @brief selectedMapPath set the map image path, default map image is map_2.png
     */
    QString selectedMapPath{":map_2.png"};
    /**
     * @brief selectedConfigPath set the map config path, default map config is map_2.txt
     */
    QString selectedConfigPath{":map_2.txt"};
};
#endif // MAINWINDOW_H
