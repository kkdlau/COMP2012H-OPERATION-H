#include "networkpage.h"
#include "ui_networkpage.h"
#include "clientpage.h"
#include <QMessageBox>

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

void NetworkPage::on_pushButton_clicked()
{
    if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()) {
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, QString{"Please choose between host and client"}, QMessageBox::Ok, this};
        msg.exec();
        return;
    } else {
        // Host radio button checked
        if (ui->radioButton->isChecked()) {
            ClientPage client_page;
            client_page.setModal(true);
            client_page.exec();
        }
        // Client radio button checked
        else {

        }
    }
}

void NetworkPage::on_pushButton_2_clicked()
{
   this->close();
}
