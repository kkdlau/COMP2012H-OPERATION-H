//#include <QNetworkInterface>

//#include "tcpserver.h"

//TCPServer::TCPServer(QObject *parent) :
//    QTcpServer(parent)
//{
//    if (!listen()) {
//        qDebug("Unable to start the server");
//        close();
//        return;
//    }
//    server_port = serverPort();

//    // Find a usable IP address
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//    for (int i = 0; i < ipAddressesList.size(); ++i) {
//        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//                ipAddressesList.at(i).toIPv4Address()) {
//            server_ip = ipAddressesList.at(i).toString();
//            break;
//        }
//    }

//    if (server_ip.isEmpty())
//        server_ip = QHostAddress(QHostAddress::LocalHost).toString();
//}

//QString TCPServer::get_ip() const {
//    return server_ip;
//}

//quint16 TCPServer::get_tcp_port() const {
//    return server_port;
//}

//QList<ServiceWorker*> TCPServer::get_clients() const {
//    return clients;
//}

//void TCPServer::incomingConnection(qintptr socketDesriptor) {
//    qDebug("New Player");
//    ServiceWorker *worker = new ServiceWorker(this);
//    if (!worker->setSocketDescriptor(socketDesriptor)) {
//        worker->deleteLater();
//        return;
//    }

//    // If the room has already full, no new player is accepted
//    if (clients.size() >= 5) {
//        QJsonObject playerFullMsg;
//        playerFullMsg["type"] = "playerFull";
//        sendJson(worker, playerFullMsg);
//        connect(worker, &ServiceWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
//        qDebug() << fullList;
//        return;
//    }

//    // Send the players list to the new player
//    if (!clients.isEmpty()) {
//        qDebug("Send player list");
//        QJsonObject playerNamesMsg;
//        QJsonArray playerNames;
//        for (ServiceWorker *worker : clients)
//            playerNames.append(worker->getPlayerName());
//        playerNamesMsg["type"] = "playerList";
//        playerNamesMsg["playerNames"] = playerNames;
//        sendJson(worker, playerNamesMsg);
//    }

//    connect(worker, &ServiceWorker::disconnectedFromClient, this, std::bind(&Server::userDisconnected, this, worker));
//    connect(worker, &ServiceWorker::jsonReceived, this, std::bind(&Server::jsonReceived, this, worker, std::placeholders::_1));
//    clients.append(worker);
//}

///*
// *  void Server::jsonReceived(ServerWorker *sender, const QJsonObject &json)
// *  @funct:  handler for when the server recieves a QJsonObject from a client
// *  @param:  sender: the client who sent the QJsonObject, json: the QJsonObject recieved
// *  @return: N/A
// */
//void TCPServer::jsonReceived(ServiceWorker *sender, const QJsonObject &json) {
//    Q_ASSERT(sender);

//    qDebug("Server Receive a Client Json");
//    const QString type = json.value(QString("type")).toString();
//    if (type == "playerName") {
//        const QString playerName = json.value("playerName").toString();

//        // If the player has the same name with existing player, server won't allow the player to enter the room
//        for (ServiceWorker *worker : clients) {
//            if (worker == sender)
//                continue;
//            if (worker->getPlayerName() == playerName) {
//                QJsonObject playerRepeatNameMsg;
//                playerRepeatNameMsg["type"] = "nameRepeat";
//                sendJson(sender, playerRepeatNameMsg);
//                fullList.append(sender);
//                clients.removeAll(sender);
//                return;
//            }
//        }

//        sender->setPlayerName(playerName);
//        QJsonObject newPlayerMsg;
//        newPlayerMsg["type"] = "newPlayer";
//        newPlayerMsg["playerName"] = playerName;
//        broadcast(newPlayerMsg);
//    }

//    emit receiveJson(sender, json);
//}

//void TCPServer::startGameBroadcast() {
//    if (clients.size()>5){
//        QMessageBox::information(nullptr, QString("Too Many Players"), QString("There are too many players."));
//        return;
//    }
//    if (clients.size()==1){
//        QMessageBox::information(nullptr, QString("Not Enough Players"), QString("You need 2-5 players to play."));
//        return;
//    }
//    qDebug("Server Start Game Broadcast");
//    QJsonObject startGameMsg;
//    startGameMsg["type"] = "startGame";
//    broadcast(startGameMsg);
//}

//void TCPServer::userDisconnected(ServiceWorker *sender) {
//    qDebug("user disconnect");
//    if (std::find(clients.begin(), clients.end(), sender) == clients.end()) {
//        fullList.removeAll(sender);
//        return;
//    }
//    clients.removeAll(sender);
//    const QString player = sender->getPlayerName();
//    if (!player.isEmpty()) {
//        QJsonObject disconnectedMessage;
//        disconnectedMessage["type"] = QString("playerDisconnected");
//        disconnectedMessage["playerName"] = player;
//        broadcast(disconnectedMessage, nullptr);
//    }
//    sender->deleteLater();
//}

//void TCPServer::sned_text(ServiceWorker *worker, const QString &text) {
//    Q_ASSERT(worker);
//    worker->(json);
//}

//void TCPServer::broadcast(const QString &text, ServiceWorker *exclude) {
//    qDebug("Broadcast Message");
//    for (ServiceWorker *worker : clients) {
//        Q_ASSERT(worker);
//        if (worker == exclude)
//            continue;
//        sendJson(worker, text);
//    }
//}

//void TCPServer::stopServer() {
//    for (ServiceWorker *worker : clients)
//        worker->disconnect_from_client();
//    close();
//}
