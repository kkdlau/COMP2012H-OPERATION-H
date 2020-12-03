#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "mapviewpage.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QTcpServer;
QT_END_NAMESPACE

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    void set_game_page(MapViewPage* input_page);

private slots:
    void send_game_stat();

    void open_game_page();
private:
    void initServer();

    QLabel *statusLabel = nullptr;
    QTcpServer *tcpServer = nullptr;
    QVector<QString> fortunes;
    MapViewPage* game_page;
};

#endif
