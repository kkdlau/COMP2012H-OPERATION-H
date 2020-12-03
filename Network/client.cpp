#include <QtWidgets>
#include <QtNetwork>

#include "client.h"
#include "mapviewpage.h"
//! [0]
Client::Client(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , getFortuneButton(new QPushButton(tr("Connect to Server")))
    , tcpSocket(new QTcpSocket(this))
    , game_page(new MapViewPage())
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
//! [0]
    hostCombo->setEditable(true);
    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    auto portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);

    statusLabel = new QLabel(tr("Fuck you all "
                                "Why would you read this"));

    getFortuneButton->setDefault(true);
    getFortuneButton->setEnabled(false);

    auto quitButton = new QPushButton(tr("Quit"));
    auto sendButton = new QPushButton(tr("Send"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//! [1]
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
//! [1]

    connect(hostCombo, &QComboBox::editTextChanged,
            this, &Client::enableGetFortuneButton);
    connect(portLineEdit, &QLineEdit::textChanged,
            this, &Client::enableGetFortuneButton);
    connect(getFortuneButton, &QAbstractButton::clicked,
            this, &Client::start_connection);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(tcpSocket, &QIODevice::readyRead, this, &Client::readFortune);
    connect(tcpSocket, &QIODevice::readyRead, this, &Client::send_game_stat);
    connect(tcpSocket, &QAbstractSocket::errorOccurred,
            this, &Client::displayError);

    QGridLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
//! [5]
}

void Client::start_connection()
{
    getFortuneButton->setEnabled(false);
    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
}

void Client::readFortune()
{
    in.startTransaction();

    QString current_stat;
    in >> current_stat;

    if (!in.commitTransaction())
        return;

    if (current_stat == "Connected") {
        send_game_stat();
    }


    statusLabel->setText(current_stat);
    getFortuneButton->setEnabled(true);

    in.abortTransaction();
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

    getFortuneButton->setEnabled(true);
}

void Client::set_game_page(MapViewPage* input_page) {
    game_page = input_page;
}

void Client::compose_game_stats() {
    QList<Character*> list_of_characters = game_page->get_character_manager()->get_all_characters();
    game_stats << tr("START");
    for (int i = 0; i < list_of_characters.size(); i++) {
        game_stats << tr(QString(QString("Character")+ i).toStdString().c_str())
                   << tr(list_of_characters.at(i)->get_name().toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->getPositionX()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->getPositionY()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->rotation()).toStdString().c_str())
                   << tr(QString::number(list_of_characters.at(i)->get_health()).toStdString().c_str());
    }
    game_stats << tr("END");
}


void Client::send_game_stat() {
    // Some previous settings
    qDebug("Sending game stats from the client side");
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    // TODO: Send the list of game stats
    compose_game_stats();
    for (int i = 0; i < game_stats.size(); i++)
    out << game_stats[i];

//    connect(clientConnection, &QAbstractSocket::disconnected,
//            clientConnection, &QObject::deleteLater);

    tcpSocket->write(block);
//    clientConnection->disconnectFromHost();
    game_stats.clear();
}

void Client::enableGetFortuneButton()
{
    getFortuneButton->setEnabled(!hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());

}
