// DO NOT CHANGE THIS FILE
// This is the new server
// being made by Stardust

#include "server.h"

#include <QtWidgets>
#include <QtNetwork>

Server::Server(QWidget *parent)
    : QDialog(parent)
    , statusLabel(new QLabel)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    init_server();

    game_stat << tr("Hello");

    auto quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    //! [3]
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::send_game_stats);
    //! [3]

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
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
}

void Server::init_server()
{
//! [0] //! [1]
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
//! [0]
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
//! [1]
}

void Server::send_game_stats()
{
//! [5]
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << game_stat[QRandomGenerator::global()->bounded(game_stat.size())];
//! [4] //! [7]

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
//! [7] //! [8]

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
//! [5]
}
//Server::Server(QWidget *parent)
//    : QDialog(parent)
//{
//    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

//    server = new QLocalServer(this);
//    if (!server->listen("operation_h")) {
//        QMessageBox::critical(this, tr("Operation H Server"),
//                              tr("Unable to start the server: %1.")
//                              .arg(server->errorString()));
//        close();
//        return;
//    }

//    QLabel *statusLabel = new QLabel;
//    statusLabel->setWordWrap(true);
//    statusLabel->setText(tr("The server is running.\n"
//                            "Run the game Operation H now."));

////    actions << tr("attack")
////            << tr("charge")
////            << tr("move");

//    QPushButton *quitButton = new QPushButton(tr("Quit"));
//    quitButton->setAutoDefault(false);
//    connect(quitButton, &QPushButton::clicked, this, &Server::close);
//    connect(server, &QLocalServer::newConnection, this, &Server::sendGamestats);

//    QHBoxLayout *buttonLayout = new QHBoxLayout;
//    buttonLayout->addStretch(1);
//    buttonLayout->addWidget(quitButton);
//    buttonLayout->addStretch(1);

//    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(statusLabel);
//    mainLayout->addLayout(buttonLayout);

//    setWindowTitle(QGuiApplication::applicationDisplayName());
//}

//void Server::sendAction()
//{
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_10);
//    const int fortuneIndex = QRandomGenerator::global()->bounded(0, actions.size());
//    const QString &message = actions.at(fortuneIndex);
//    out << quint32(message.size());
//    out << message;

//    QLocalSocket *clientConnection = server->nextPendingConnection();
//    connect(clientConnection, &QLocalSocket::disconnected,
//            clientConnection, &QLocalSocket::deleteLater);

//    clientConnection->write(block);
//    clientConnection->flush();
//    clientConnection->disconnectFromServer();
//}

//void Server::sendGamestats()
//{
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_10);
////    const int fortuneIndex = QRandomGenerator::global()->bounded(0, actions.size());
////    const QString &message = actions.at(fortuneIndex);
//    const QString message = generateGamestats(nullptr);
//    out << quint32(message.size());
//    out << message;

//    QLocalSocket *clientConnection = server->nextPendingConnection();
//    connect(clientConnection, &QLocalSocket::disconnected,
//            clientConnection, &QLocalSocket::deleteLater);

//    clientConnection->write(block);
//    clientConnection->flush();
//    clientConnection->disconnectFromServer();
//}

////QString Server::generateGamestats(Character* character) {
////    QString character_stats = "";
////    character_stats = character->get_name() + " ";
////    character_stats = character_stats + QString::number(character->get_health()) + " ";
////    character_stats = character_stats + QString::number(character->getPositionX()) + " ";
////    character_stats = character_stats + QString::number(character->getPositionY()) + " ";
////    return character_stats;
////}

//// dummy
//QString Server::generateGamestats(Character* character) {
//    QString character_stats = "";
//    character_stats += "A"; character_stats += " ";
//    character_stats += QString::number(100); character_stats += " ";
//    character_stats += QString::number(10); character_stats += " ";
//    character_stats += QString::number(20);
//    return character_stats;
//}
