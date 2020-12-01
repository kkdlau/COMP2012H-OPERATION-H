#include "clientpage.h"
#include "ui_clientpage.h"
#include "Network/tcpclient.h"
#include "QHostAddress"

ClientPage::ClientPage(QWidget *parent) :
    QDialog(parent),
    tcp_client(new TCPClient(this)),
    ui(new Ui::ClientPage)
{
    ui->setupUi(this);
    connect(tcp_client, &TCPClient::connected,this, &ClientPage::debug_connected);
    connect(tcp_client, &TCPClient::disconnected,this, &ClientPage::debug_disconnected);
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
    tcp_client->connect_to_server(QHostAddress(ui->lineEdit->text()), OUR_PORT);

}
