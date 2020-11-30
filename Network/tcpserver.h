//#ifndef TCPSERVER_H
//#define TCPSERVER_H

//#include <QObject>
//#include <QTcpSocket>
//#include <QTcpServer>

//class TCPServer : public QTcpServer
//{
//    Q_OBJECT

//public:
//    explicit TCPServer(QObject *parent = nullptr);

//    void connect_to_client(const QTcpSocket client_socket);  // me
//    void disconnect_from_client();  // me

//    QString get_ip() const;
//    quint16 get_tcp_port() const;
//    QTcpSocket get_socket() const;

//    template <class T>
//    void receive_from_client(T raw_data);  // me

//public slots:
//    void broadcast(QString message);

//private:
//    quint16 server_port;
//    QString server_ip;
//    QList<ServiceWorker*> clients;

//    QTcpSocket client_socket;
//    void text_received(const QString &text);
//};

//#endif // TCPSERVER_H
