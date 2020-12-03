#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QDialog>
#include "mapviewpage.h"

namespace Ui {
class NetworkPage;
}

class NetworkPage : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkPage(QWidget *parent = nullptr);
    ~NetworkPage();
    void set_game_page(MapViewPage*);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::NetworkPage *ui;
    MapViewPage* game_page;
};

#endif // NETWORKPAGE_H
