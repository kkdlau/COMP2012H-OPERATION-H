#include "clientpage.h"
#include "ui_clientpage.h"
#include "Network/tcpclient.h"
#include "QHostAddress"
#include <QMessageBox>
#include <QDialog>


ClientPage::ClientPage(QWidget *parent) :
    QDialog(parent),
    tcp_client(new TCPClient(this)),
    ui(new Ui::ClientPage)
{
    ui->setupUi(this);
    connect(tcp_client, &TCPClient::connected,this, &ClientPage::debug_connected);
    connect(tcp_client, &TCPClient::disconnected,this, &ClientPage::debug_disconnected);
    connect(tcp_client->get_client_socket(), &QAbstractSocket::errorOccurred,this, &ClientPage::display_error);
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
    tcp_client->connect_to_server(QHostAddress(ui->lineEdit->text()), quint16(OUR_PORT));
}

void ClientPage::display_error(QAbstractSocket::SocketError socketError)
{
    QString err_msg;
    if (socketError == QAbstractSocket::RemoteHostClosedError) {
        err_msg = "The host closed the remote host.";
        qDebug() << err_msg;
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, err_msg, QMessageBox::Ok, this};
        msg.exec();
    }
    else if (socketError == QAbstractSocket::HostNotFoundError) {
        err_msg = "The host was not found.";
        qDebug() << err_msg;
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, err_msg, QMessageBox::Ok, this};
        msg.exec();
    }

    else if (socketError == QAbstractSocket::ConnectionRefusedError) {
        err_msg = "The connection was refused by the host";
        qDebug() << err_msg;
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, err_msg, QMessageBox::Ok, this};
        msg.exec();
    }
    else {
        err_msg = tcp_client->get_client_socket()->errorString();
        qDebug() << err_msg;
        QMessageBox msg{QMessageBox::Critical, QString{"Error"}, err_msg, QMessageBox::Ok, this};
        msg.exec();
    }
}

