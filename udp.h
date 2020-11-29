#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    void say_hello_in_udp(QString);

signals:

public slots:
    void read_from_udp();

private:
    // The socket for connecting to the other person
    QUdpSocket * socket;
};

#endif // UDP_H
