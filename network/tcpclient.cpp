#include "tcpclient.h"

// Public
// Please put mainwindow to the parameter
TCPClient::TCPClient(QObject *parent) : QObject(parent), client_socket(new QTcpSocket(this)) {
    // signal relay
    connect(client_socket, &QTcpSocket::connected, this, &TCPClient::connected);
    connect(client_socket, &QTcpSocket::disconnected, this, &TCPClient::disconnected);
    connect(client_socket, &QTcpSocket::readyRead, this, &TCPClient::on_ready_read);

}

void TCPClient::connect_to_server(const QHostAddress &server_address, quint16 server_port) {
    qDebug() << "Attempting to connect to server";
    client_socket->abort();
//    qDebug() << "Server Address: " << server_address;
    qDebug() << "Server Port: " << server_port;
    client_socket->connectToHost(server_address, server_port);

}

QTcpSocket* TCPClient::get_client_socket() const {
    return client_socket;
}

void TCPClient::disconnect_from_server() {
    client_socket->disconnectFromHost();
    qDebug() << "Client disconnected from server";
}

void TCPClient::send_text(const QString &text) {
    QDataStream clientStream(client_socket);

    //  Not sure if this is needed or not
    clientStream.setVersion(QDataStream::Qt_5_11);
    clientStream << text;
}

// public slot



// Signals
void TCPClient::on_ready_read() {
    qDebug("Client ready for reading");
    QByteArray text_to_send;
    QDataStream socket_stream(client_socket);
    socket_stream.setVersion(QDataStream::Qt_5_11);

    while (true) {
        socket_stream.startTransaction();
        socket_stream >> text_to_send;
        if (socket_stream.commitTransaction()) {
            emit text_received(text_to_send);
        } else break;
    }
}

// Private
void TCPClient::text_received(const QString &text) {
    emit receive_text(text);
}
