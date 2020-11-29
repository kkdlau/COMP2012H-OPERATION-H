#include "udp.h"
#include <QDebug>
#include "mainwindow.h"

#define OUR_PORT 6969

UDP::UDP(QObject *parent) : QObject(parent) {
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, OUR_PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(read_from_udp()) );
}

void UDP::say_hello_in_udp(QString raw_data) {
        QByteArray data;
        QHostAddress target_address;
//        target_address.setAddress("10.89.117.107");
        target_address.setAddress("127.0.0.1");
        data.append("Steven");
        socket->writeDatagram(data, QHostAddress::Broadcast, OUR_PORT);
}

void UDP::read_from_udp() {
    // Making the buffer for reading
    QByteArray buffer;
    buffer.resize(1024);
    // All the networking related stuff
    QHostAddress sender;
    quint16 sender_port;
    socket->readDatagram(buffer.data(), buffer.size(),&sender, &sender_port);

    qDebug() << "Sender" <<  sender;
    qDebug() << "Sender Port" << sender_port;
    qDebug() << "Received data" <<buffer.data();
}
