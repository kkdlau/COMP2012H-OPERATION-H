#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QString>

#include "server.h"

Server::Server(QWidget *parent)
    : QDialog(parent)
    , statusLabel(new QLabel)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    initServer();

    QPushButton* quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::exec_game_page);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::send_connected_signal);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        QVBoxLayout* outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        QHBoxLayout* outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        QGroupBox* groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QVBoxLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QVBoxLayout(this);
    }

    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(QGuiApplication::applicationDisplayName());
//    compose_game_stats();
    game_stats << tr("Connected");
}

void Server::initServer()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Host"),
                              tr("Ha Ha do you not have a NIC card in your computer: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    // Finding your actual ip address
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            qDebug() << (address.toString());
            statusLabel->setText(tr("Server Information:\n\nIP: %1\nport: %2\n\n")
                                 .arg(address.toString()).arg(tcpServer->serverPort()));
        }
    }
}

void Server::open_game_page() {
    // Some previous settings
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    // Sending the data out
    out << tr("Connected");

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);
    clientConnection->disconnectFromHost();

    // Opening the actual game page;
    game_page->setModal(true);
    game_page->exec();
}

void Server::compose_game_stats() {
    QList<Character*> list_of_characters = game_page->get_character_manager()->get_all_characters();
    game_stats << tr("START");
    for (int i = 0; i < list_of_characters.size(); i++) {
        game_stats << tr(QString(QString("Character")+ i).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->getPositionX()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->getPositionY()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->rotation()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->get_health()).toStdString().c_str());
    }
    game_stats << tr("END");
}

void Server::set_game_page(MapViewPage* input_page) {
    game_page = input_page;
}

void Server::exec_game_page() {
    game_page->setModal(true);
    game_page->exec();
}

void Server::send_connected_signal() {
    QString connected_string("Connected");
    game_stats << connected_string;
}


void Server::send_game_stat() {
    // Setting up the reading streams and arrays
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    // TODO: Send the list of game stats [OK I didn't actually do it in the end cuz I don't know why
    // the server can't even receive stuff and emit signal]
    out << game_stats[0];

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    clientConnection->write(block);
    game_stats.clear();
}
