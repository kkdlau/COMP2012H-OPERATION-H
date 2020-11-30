#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) : QTcpServer(parent), server_socket(new QTcpSocket(this)), connected_to_client(false)
{
    // NOT DONE!!!
}

void TCPServer::save_client_info(const QTcpSocket client_socket) {
    client_tcp_port = client_socket.peerPort();
    client_address = client_socket.peerAddress();
}

void TCPServer::connect_to_client(const QTcpSocket client_socket) {
//    save_client_info(client_socket);
    qDebug() << "Attempting to connect to client";
    qDebug() << "Client Port" << client_tcp_port;
    qDebug() << "Client Address" << client_address;
    server_socket.connectToHost(client_address, client_tcp_port);
}

QString TCPServer::get_ip() const {
    return server_ip;
}

quint16 TCPServer::get_tcp_port() const {
    return server_tcp_port;
}

//QTcpSocket TCPServer::get_socket() const {
//    return server_socket;
//}
