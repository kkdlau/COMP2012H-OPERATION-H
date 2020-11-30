#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent)
{

}

QString TCPServer::get_ip() const {
    return ip;
}

quint16 TCPServer::get_tcp_port() const {
    return tcp_port;
}
