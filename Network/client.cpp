#include <QtWidgets>
#include <QtNetwork>

#include "client.h"

//! [0]
Client::Client(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , get_game_stat_Button(new QPushButton(tr("Get Game Stat")))
    , tcpSocket(new QTcpSocket(this))
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

    statusLabel = new QLabel(tr("This examples requires that you run the "
                                "Fortune Server example as well."));

    get_game_stat_Button->setDefault(true);
    get_game_stat_Button->setEnabled(false);

    auto quitButton = new QPushButton(tr("Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(get_game_stat_Button, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//! [1]
    input.setDevice(tcpSocket);
    input.setVersion(QDataStream::Qt_4_0);
//! [1]

    connect(hostCombo, &QComboBox::editTextChanged,
            this, &Client::enable_get_game_stat_button);
    connect(portLineEdit, &QLineEdit::textChanged,
            this, &Client::enable_get_game_stat_button);
    connect(get_game_stat_Button, &QAbstractButton::clicked,
            this, &Client::request_game_stat);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
//! [2] //! [3]
    connect(tcpSocket, &QIODevice::readyRead, this, &Client::read_game_stat);
//! [2] //! [4]
    connect(tcpSocket, &QAbstractSocket::errorOccurred,
//! [3]
            this, &Client::displayError);
//! [4]

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
//! [5]

//! [6]
void Client::request_game_stat()
{
    get_game_stat_Button->setEnabled(false);
    tcpSocket->abort();
//! [7]
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
//! [7]
}
//! [6]

//! [8]
void Client::read_game_stat()
{
    input.startTransaction();

    QString next_game_stat;
    input >> next_game_stat;

    if (!input.commitTransaction())
        return;

    if (next_game_stat == current_game_stat) {
        QTimer::singleShot(0, this, &Client::request_game_stat);
        return;
    }

    current_game_stat = next_game_stat;
    statusLabel->setText(current_game_stat);
    get_game_stat_Button->setEnabled(true);
}
//! [8]

//! [13]
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

    get_game_stat_Button->setEnabled(true);
}
//! [13]

void Client::enable_get_game_stat_button()
{
    get_game_stat_Button->setEnabled(!hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());

}


//#include <QtWidgets>
//#include <QtNetwork>

//#include "client.h"

//Client::Client(QWidget *parent)
//    : QDialog(parent),
//      hostLineEdit(new QLineEdit("operation_h")),
//      getActionButton(new QPushButton(tr("Get Action"))),
//      statusLabel(new QLabel(tr("Enter the server name "
//                                "to join a game."))),
//      socket(new QLocalSocket(this))
//{
//    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
//    QLabel *hostLabel = new QLabel(tr("&Server name:"));
//    hostLabel->setBuddy(hostLineEdit);

//    statusLabel->setWordWrap(true);

//    getActionButton->setDefault(true);
//    QPushButton *quitButton = new QPushButton(tr("Quit"));

//    QDialogButtonBox *buttonBox = new QDialogButtonBox;
//    buttonBox->addButton(getActionButton, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//    in.setDevice(socket);
//    in.setVersion(QDataStream::Qt_5_10);

//    connect(hostLineEdit, &QLineEdit::textChanged,
//            this, &Client::enableGetActionButton);
//    connect(getActionButton, &QPushButton::clicked,
//            this, &Client::requestNewAction);
//    connect(quitButton, &QPushButton::clicked, this, &Client::close);
//    connect(socket, &QLocalSocket::readyRead, this, &Client::readAction);
//    connect(socket, &QLocalSocket::errorOccurred, this, &Client::displayError);

//    QGridLayout *mainLayout = new QGridLayout(this);
//    mainLayout->addWidget(hostLabel, 0, 0);
//    mainLayout->addWidget(hostLineEdit, 0, 1);
//    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
//    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

//    setWindowTitle(QGuiApplication::applicationDisplayName());
//    hostLineEdit->setFocus();
//}

//void Client::requestNewAction()
//{
//    getActionButton->setEnabled(false);
//    blockSize = 0;
//    socket->abort();
//    socket->connectToServer(hostLineEdit->text());
//}

//void Client::readAction()
//{
//    if (blockSize == 0) {
//        // Relies on the fact that QDataStream serializes a quint32 into
//        // sizeof(quint32) bytes
//        if (socket->bytesAvailable() < (int)sizeof(quint32))
//            return;
//        in >> blockSize;
//    }

//    if (socket->bytesAvailable() < blockSize || in.atEnd())
//        return;

//    QString nextAction;
//    in >> nextAction;

//    if (nextAction == currentAction) {
//        QTimer::singleShot(0, this, &Client::requestNewAction);
//        return;
//    }

//    currentAction = nextAction;
//    statusLabel->setText(currentAction);
//    getActionButton->setEnabled(true);
//}

//void Client::displayError(QLocalSocket::LocalSocketError socketError)
//{
//    switch (socketError) {
//    case QLocalSocket::ServerNotFoundError:
//        QMessageBox::information(this, tr("Operation H Client"),
//                                 tr("The host was not found. Please make sure "
//                                    "that the server is running and that the "
//                                    "server name is correct."));
//        break;
//    case QLocalSocket::ConnectionRefusedError:
//        QMessageBox::information(this, tr("Operation H Client"),
//                                 tr("The connection was refused by the peer. "
//                                    "Make sure the fortune server is running, "
//                                    "and check that the server name "
//                                    "is correct."));
//        break;
//    case QLocalSocket::PeerClosedError:
//        break;
//    default:
//        QMessageBox::information(this, tr("Local Fortune Client"),
//                                 tr("The following error occurred: %1.")
//                                 .arg(socket->errorString()));
//    }

//    getActionButton->setEnabled(true);
//}

//void Client::enableGetActionButton()
//{
//    getActionButton->setEnabled(!hostLineEdit->text().isEmpty());
//}
