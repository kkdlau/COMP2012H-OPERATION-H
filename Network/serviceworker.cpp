#include "serviceworker.h"

ServiceWorker::ServiceWorker(QObject *parent):
    QObject(parent),
    server_socket(new QTcpSocket(this))
{
    qDebug("New ServerWorker");
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
}

void ServiceWorker::disconnect_from_client() {
}

void ServiceWorker::receive_text() {
}

void ServiceWorker::send_text(const QString &text) {
}
