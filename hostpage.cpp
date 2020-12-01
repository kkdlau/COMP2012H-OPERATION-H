#include "hostpage.h"
#include "ui_hostpage.h"
#include <QNetworkInterface>

HostPage::HostPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostPage)
{
    ui->setupUi(this);
    update_ip();
}

HostPage::~HostPage()
{
    delete ui;
}

void HostPage::update_ip(){
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            qDebug() << (address.toString());
            ui->label_4->setText(address.toString());
        }
    }
}
