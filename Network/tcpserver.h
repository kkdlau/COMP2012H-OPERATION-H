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
    QString get_ip() const;
    QString get_tcp_port() const;

public slots:
//    void broadcast(QString message);

private:
    quint16 tcp_port;
    QString ip;
    QTcpServer tcp_server;
    QList<QTcpSocket*> sockets;
};

#endif // TCPSERVER_H
