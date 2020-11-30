#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include "serviceworker.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit TCPServer(QObject *parent = nullptr);

    QString get_ip() const;
    quint16 get_tcp_port() const;
    QList<ServiceWorker*> get_clients() const;

protected:
    void incomingConnection(qintptr socket_descriptor) override;

signals:
    void receive_text(ServiceWorker *sender, const QString &text);

public slots:
    void stopServer();
    void startGameBroadcast();
    void broadcast(const QString &message, ServiceWorker *exclude = nullptr);

private slots:
    void text_received(ServiceWorker *sender, const QString &text);
    void user_disconnectedd(ServiceWorker *sender);

private:
    quint16 server_port;
    QString server_ip;
    QList<ServiceWorker*> clients;
    QList<ServiceWorker*> list;
    void send_text(ServiceWorker *worker, const QString &text);
};

#endif // TCPSERVER_H
