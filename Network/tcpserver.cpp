//#include "tcpserver.h"

//TCPServer::TCPServer(QObject *parent) : QTcpServer(parent), server_socket(new QTcpSocket(this)), connected_to_client(false)
//{
//    // NOT DONE!!!
//}

//void TCPServer::connect_to_client(const QTcpSocket client_socket) {
//    client_tcp_port = client_socket.peerPort();
//    client_address = client_socket.peerAddress();

//    qDebug() << "Attempting to connect to client";
//    qDebug() << "Client Port: " << client_tcp_port;
//    qDebug() << "Client Address: " << client_address;

//    server_socket.connectToHost(client_address, client_tcp_port);
//}

//QString TCPServer::get_ip() const {
//    return server_ip;
//}

//quint16 TCPServer::get_tcp_port() const {
//    return server_tcp_port;
//}

//template <class T>
//void TCPServer::receive_from_client(T raw_data) {
//    QDataStream clientStream();
//}
