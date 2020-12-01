#include "clientpage.h"
#include "ui_clientpage.h"
#include <QNetworkInterface>

ClientPage::ClientPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientPage)
{
    update_ip();
    ui->setupUi(this);
}

ClientPage::~ClientPage()
{
    delete ui;
}

void ClientPage::update_ip(){
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             qDebug() << address.toString();
    }
}
