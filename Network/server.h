#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QTcpSocket>
#include <QTimer>
#include "mapviewpage.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    void set_game_page(MapViewPage* input_page);

private slots:
    void send_game_stat();
    void exec_game_page();
    void open_game_page();
    void send_connected_signal();
    void debug_timer();
    void debug_readyread();
private:
    void compose_game_stats();
    void save_client_info();
    void initServer();
    void read_game_stat();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QVector<QString> game_stats;
    QTcpSocket *clientConnection;
    MapViewPage* game_page;
    QTimer* timer;
    QDataStream in;
};

#endif
