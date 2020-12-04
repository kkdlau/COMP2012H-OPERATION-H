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

    /**
     * @brief Getting the mapviewpage from network page so that only one instance of mapviewpage is instantiated
     * @param input_page
     */
    void set_game_page(MapViewPage* input_page);

private slots:

    /**
     * @brief Sending game stats to the client side
     *        Game stats include players position, rotation and health
     */
    void send_game_stat();

    /**
     * @brief Execute the game page to start the game
     */
    void exec_game_page();

    /**
     * @brief Open the game page, which is just showing the game_page
     */
    void open_game_page();

    /**
     * @brief Sending a connected signal to the client side once there is a new connection
     */
    void send_connected_signal();
private:
    /**
     * @brief Compose the game stats and put it into the vector of qstring called game_stats
     */
    void compose_game_stats();

    /**
     * @brief Initializing the server by opening a socket
     */
    void initServer();

    /**
     * @brief The status label on the window so that it shows the current status of the server
     */
    QLabel *statusLabel = nullptr;

    /**
     * @brief The tcp server instance that is instantiated for detecting connection
     */
    QTcpServer *tcpServer = nullptr;

    /**
     * @brief A vector of q string that stores  game stats to be sent to the client side
     */
    QVector<QString> game_stats;

    /**
     * @brief game_page shows the current screen for the game
     */
    MapViewPage* game_page;
};

#endif
