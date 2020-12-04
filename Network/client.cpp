#include <QtWidgets>
#include <QtNetwork>
#include "client.h"
#include "mapviewpage.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , connect_button(new QPushButton(tr("Connect to Server")))
    , tcp_socket(new QTcpSocket(this))
{
    // Some setup for the UI
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    hostCombo->setEditable(true);

    // Find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));

    // Find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // Add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    // Add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    // Validation for the port
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    // Adding labels
    QLabel* hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    QLabel* portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);

    // For fun and for debugging what you received
    statusLabel = new QLabel(tr("Why would you read this"));

    // Making the connect button usable
    connect_button->setDefault(true);
    connect_button->setEnabled(false);

    // Dynamically instantiating a quit button
    QPushButton* quitButton = new QPushButton(tr("Quit"));

    // Making even more buttons for the users to use
    QDialogButtonBox* buttonBox = new QDialogButtonBox;
    buttonBox->addButton(connect_button, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    // Connecting the input datastream with the tcp socket
    in.setDevice(tcp_socket);
    in.setVersion(QDataStream::Qt_4_0);

    // Just a bunch of connects so that the buttons can work and the client can read from the server's message
    connect(hostCombo, &QComboBox::editTextChanged,
            this, &Client::enable_connect_button);
    connect(portLineEdit, &QLineEdit::textChanged,
            this, &Client::enable_connect_button);
    connect(connect_button, &QAbstractButton::clicked,
            this, &Client::send_game_stat);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(tcp_socket, &QIODevice::readyRead, this, &Client::read_game_stat);
    connect(tcp_socket, &QAbstractSocket::errorOccurred,
            this, &Client::displayError);

    // The actual layout (I copied from the Internet so that I don't have to design it myself cuz I am bad at doing it)
    QGridLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        QVBoxLayout* outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        QHBoxLayout* outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        QGroupBox* groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    // Adding Widget to the layout so that they can be properly formatted
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
}

void Client::send_game_stat()
{
    connect_button->setEnabled(false);
    tcp_socket->abort();
    tcp_socket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
}

void Client::read_game_stat()
{
    in.startTransaction();

    QString current_stat;
    in >> current_stat;

    if (!in.commitTransaction())
        return;

    statusLabel->setText(current_stat);
    connect_button->setEnabled(true);

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
                                 .arg(tcp_socket->errorString()));
    }

    connect_button->setEnabled(true);
}

void Client::set_game_page(MapViewPage* input_page) {
    game_page = input_page;
}

void Client::enable_connect_button()
{
    connect_button->setEnabled(!hostCombo->currentText().isEmpty() && !portLineEdit->text().isEmpty());
}
