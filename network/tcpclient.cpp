#include "tcpclient.h"

// Public
// Please put mainwindow to the parameter
TCPClient::TCPClient(QObject *parent) : QObject(parent), client_socket(new QTcpSocket(this)), connected_to_host(false)
{
    connect(client_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(client_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void TCPClient::connect_to_host(const QHostAddress host_address, quint16 port) {
    qDebug() << "Attempting to connect to host";
    qDebug() << "Host Address" << host_address;
    qDebug() << "Host Port" << host_port;
    client_socket->connectToHost(host_address, port);
}

void TCPClient::disconnect_from_host() {
    client_socket->disconnectFromHost();
}

QHostAddress TCPClient::get_host_address() const {
    return host_address;
}

quint16 TCPClient::get_host_port() const {
    return host_port;
}

// Public Slots
void TCPClient::connected() {
    qDebug() << "Connected to host";
    connected_to_host = true;
    host_address = client_socket->peerAddress();
    host_port = client_socket->peerPort();
}

void TCPClient::disconnected() {
    qDebug() << "Disconnected from host";
    connected_to_host = false;
}

template <class T>
void TCPClient::send_to_host(T raw_data) {
    QDataStream clientStream(client_socket);
    //  Not sure if this is needed or not
    clientStream.setVersion(QDataStream::Qt_5_11);
    clientStream << raw_data;
}

// Read all the data and print it in the qdebug()
void TCPClient::ready_read() {
    QByteArray data = client_socket->readAll();
    qDebug() << data;
}
