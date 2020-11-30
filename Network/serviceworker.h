#ifndef SERVICEWORKER_H
#define SERVICEWORKER_H

#include <QObject>
#include <QTcpSocket>

class ServiceWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServiceWorker(QObject *parent = nullptr);
    virtual bool set_socket_descriptor(qintptr socket_descriptor);
    QString get_character_name() const;
    void set_character_name(const QString &name);
    void send_text(const QString &text);

signals:
    void text_received(const QString &text);
    void disconnected_from_client();

public slots:
    void disconnect_from_client();

private slots:
    void receive_text();

private:
    QTcpSocket *server_socket;
    QString character_name;
};

#endif // SERVICEWORKER_H
