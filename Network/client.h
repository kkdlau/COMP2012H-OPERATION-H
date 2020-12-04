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
    void send_game_stat();
    void read_game_stat();

    /**
     * @brief Displaying error to the user to see what is the error and hope they will try fixing it
     * @param socketError is basically the error the socket receive which can be classified into different types
     */
    void displayError(QAbstractSocket::SocketError socketError);
    void enable_connect_button();

private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *connect_button = nullptr;

    QTcpSocket *tcp_socket = nullptr;
    QDataStream in;
    QString currentFortune;
    MapViewPage* game_page;
};

#endif
