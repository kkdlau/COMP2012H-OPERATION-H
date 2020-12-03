#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QDialog>
#include <QTcpSocket>
#include "mapviewpage.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    void set_game_page(MapViewPage*);


private slots:
    void start_connection();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();

private:
    void compose_game_stats();
    void send_game_stat();
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *getFortuneButton = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;
    MapViewPage* game_page;
    QVector<QString> game_stats;
    QTcpSocket *clientConnection;
};

#endif
