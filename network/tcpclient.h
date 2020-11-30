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
public slots:
//    void connect(QHostAddress &address, quint16 port);
//    void disconnect();
private slots:
//    void onReadyRead();
signals:
//    void connected();
//    void disconnected();
//    void receive(QString);
private:
    QTcpSocket *clientSocket;
//    void send(QString);
};

#endif // TCPCLIENT_H
