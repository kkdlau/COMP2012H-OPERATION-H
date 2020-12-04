#include "networkpage.h"
#include "ui_networkpage.h"
#include <QMessageBox>
#include "Network/server.h"
#include "Network/client.h"

NetworkPage::NetworkPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkPage)
{
    ui->setupUi(this);
}

NetworkPage::~NetworkPage()
{
    delete ui;
}

void NetworkPage::set_game_page(MapViewPage* input_page) {
    game_page = input_page;
}


void NetworkPage::on_pushButton_clicked()
{
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()) {
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, QString{"Please choose between host and client"}, QMessageBox::Ok, this};
        msg.exec();
        return;
    } else {
        // Host radio button checked
        if (ui->radioButton->isChecked()) {
            Server server;
            server.set_game_page(game_page);
            server.exec();
        }
        // Client radio button checked
        else {
            Client client;
            client.set_game_page(game_page);
            client.exec();
        }
    }
}

void NetworkPage::on_pushButton_2_clicked()
{
   this->close();
}
