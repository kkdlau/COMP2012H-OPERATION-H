#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>


class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(QObject *parent = nullptr);

    void connect_to_host(const QHostAddress host_address, quint16 port);
    void disconnect_from_host();

    QHostAddress get_host_address() const;
    quint16 get_host_port() const;

    template <class T>
    void send_to_host(T);

public slots:
    void connected();
    void disconnected();
    void bytes_written(qint64);
    void ready_read();

private:
    QHostAddress host_address;
    quint16 host_port;
    QTcpSocket *client_socket;
    bool connected_to_host;
};

#endif // TCPCLIENT_H
