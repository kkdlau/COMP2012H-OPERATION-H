#include "udp.h"
#include <QDebug>
#include <QtNetwork>
#include "mainwindow.h"

#define OUR_PORT 45454

UDP::UDP(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, OUR_PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read_from_udp()),Qt::QueuedConnection );
}

void UDP::say_hello_in_udp(QString raw_data) {
        QByteArray data;
        QHostAddress target_address;
//        target_address.setAddress("192.168.1.108");
        target_address.setAddress("127.0.0.1");
        data.append("sdfgjkl;");
        socket->writeDatagram(data, QHostAddress::Broadcast, OUR_PORT);
}

void UDP::read_from_udp() {
    // My own stuff
//    // Making the buffer for reading
//    QByteArray buffer;
//    buffer.resize(256);
//    // All the networking related stuff
//    QHostAddress sender;
//    quint16 sender_port;
//    socket->readDatagram(buffer.data(), buffer.size(), &sender, &sender_port);

//    qDebug() << "Sender" <<  sender;
//    qDebug() << "Sender Port" << sender_port;
//    qDebug() << "Received data" <<buffer.data();

    QHostAddress sender;
    uint16_t port;
    while (socket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());
    }
}
