#include "clientpage.h"
#include "ui_clientpage.h"
#include "QHostAddress"
#include <QMessageBox>

ClientPage::ClientPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientPage)
{
    ui->setupUi(this);
}

void ClientPage::debug_connected(){
    qDebug() << "Connected";
}

void ClientPage::debug_disconnected() {
    qDebug() << "Disconnected";
}

ClientPage::~ClientPage()
{
    delete ui;
}

void ClientPage::on_pushButton_clicked()
{
    // TODO: IP address Validation
    qDebug() << "Attempting to connect to address in client page:"<< ui->lineEdit->text();
    qDebug() << "Attempting to connect to port in client page:"<< quint16(OUR_PORT);

}

