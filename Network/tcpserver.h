#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = nullptr);

    void connect_to_client(const QTcpSocket client_socket);  // me
    void disconnect_from_client();  // me

    QString get_ip() const;
    quint16 get_tcp_port() const;
//    QTcpSocket get_socket() const;

    template <class T>
    void receive_from_client(T);  // me

public slots:
//    void broadcast(QString message);

private:
    void save_client_info(const QTcpSocket client_socket);  // me

    // server side (aka this side) info
    QString server_ip;
    quint16 server_tcp_port;
    QTcpServer tcp_server;
    QTcpSocket server_socket;

    // client side info
    quint16 client_tcp_port;
    QString client_ip;
    QTcpSocket client_socket;  // me
    QHostAddress client_address;  // me
    int num_clients_connected{0};  // me
    bool connected_to_client;
};

#endif // TCPSERVER_H
