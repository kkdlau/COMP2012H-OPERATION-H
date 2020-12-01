#include "clientpage.h"
#include "ui_clientpage.h"
#include "Network/tcpclient.h"
#include "QHostAddress"

ClientPage::ClientPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientPage)
{
    ui->setupUi(this);
}

ClientPage::~ClientPage()
{
    delete ui;
}

void ClientPage::on_pushButton_clicked()
{
    TCPClient tcp_client;
    // TODO: IP address Validation
    tcp_client.connect_to_server(QHostAddress(ui->lineEdit->text()), OUR_PORT);

}
