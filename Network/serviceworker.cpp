#include "serviceworker.h"

ServiceWorker::ServiceWorker(QObject *parent):
    QObject(parent),
    server_socket(new QTcpSocket(this))
{
    qDebug() << "ServiceWorker for TCPServer generated";
    connect(server_socket, &QTcpSocket::readyRead, this, &ServiceWorker::receive_text);
    connect(server_socket, &QTcpSocket::disconnected, this, &ServiceWorker::disconnect_from_client);
}

bool ServiceWorker::set_socket_descriptor(qintptr socket_descriptor) {
    return server_socket->setSocketDescriptor(socket_descriptor);
}

QString ServiceWorker::get_character_name() const {
    return character_name;
}

void ServiceWorker::set_character_name(const QString &name) {
    character_name = name;
}

void ServiceWorker::disconnect_from_client() {
    server_socket->disconnectFromHost();
    emit disconnected_from_client();
}

void ServiceWorker::receive_text() {
    qDebug() << "ServiceWorker receive text";
    QByteArray text_to_receive;
    QDataStream socket_stream(server_socket);
    socket_stream.setVersion(QDataStream::Qt_5_11);
    while (true) {
        socket_stream.startTransaction();
        socket_stream >> text_to_receive;
        if (socket_stream.commitTransaction()) {
            emit text_received(text_to_receive);
        } else break;
    }
}

void ServiceWorker::send_text(const QString &text) {
    QDataStream socket_stream(server_socket);
    socket_stream.setVersion(QDataStream::Qt_5_11);
    socket_stream << text;
}
