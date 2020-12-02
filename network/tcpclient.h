#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#define OUR_PORT 45454

class TCPClient : public QObject
{
    Q_OBJECT

public:
    explicit TCPClient(QObject *parent = nullptr);
    void send_text(const QString &text);
    void displayError(QAbstractSocket::SocketError socketError);
    QTcpSocket* get_client_socket() const;

public slots:
    void connect_to_server(const QHostAddress &server_address, quint16 server_port);
    void disconnect_from_server();

private slots:
    void on_ready_read();

signals:
    void connected();
    void disconnected();
    void receive_text(const QString &text);

private:
    QTcpSocket *client_socket;
    void text_received(const QString &text);
};

#endif // TCPCLIENT_H
