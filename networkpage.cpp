#include "networkpage.h"
#include "ui_networkpage.h"
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
    }
}
