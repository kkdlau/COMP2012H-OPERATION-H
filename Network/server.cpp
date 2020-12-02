// DO NOT CHANGE THIS FILE
// This is the new server
// being made by Stardust

#include "server.h"

#include <QtWidgets>
#include <QtNetwork>

Server::Server(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    server = new QLocalServer(this);
    if (!server->listen("operation_h")) {
        QMessageBox::critical(this, tr("Operation H Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server->errorString()));
        close();
        return;
    }

    QLabel *statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    statusLabel->setText(tr("The server is running.\n"
                            "Run the game Operation H now."));

//    actions << tr("attack")
//            << tr("charge")
//            << tr("move");

    QPushButton *quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    connect(quitButton, &QPushButton::clicked, this, &Server::close);
    connect(server, &QLocalServer::newConnection, this, &Server::sendGamestats);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);

    setWindowTitle(QGuiApplication::applicationDisplayName());
}

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

void Server::sendGamestats()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
//    const int fortuneIndex = QRandomGenerator::global()->bounded(0, actions.size());
//    const QString &message = actions.at(fortuneIndex);
    const QString message = generateGamestats(nullptr);
    out << quint32(message.size());
    out << message;

    QLocalSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QLocalSocket::disconnected,
            clientConnection, &QLocalSocket::deleteLater);

    clientConnection->write(block);
    clientConnection->flush();
    clientConnection->disconnectFromServer();
}

//QString Server::generateGamestats(Character* character) {
//    QString character_stats = "";
//    character_stats = character->get_name() + " ";
//    character_stats = character_stats + QString::number(character->get_health()) + " ";
//    character_stats = character_stats + QString::number(character->getPositionX()) + " ";
//    character_stats = character_stats + QString::number(character->getPositionY()) + " ";
//    return character_stats;
//}

// dummy
QString Server::generateGamestats(Character* character) {
    QString character_stats = "";
    character_stats += "A"; character_stats += " ";
    character_stats += QString::number(100); character_stats += " ";
    character_stats += QString::number(10); character_stats += " ";
    character_stats += QString::number(20);
    return character_stats;
}
