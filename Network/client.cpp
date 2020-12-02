#include <QtWidgets>
#include <QtNetwork>

#include "client.h"

Client::Client(QWidget *parent)
    : QDialog(parent),
      hostLineEdit(new QLineEdit("operation_h")),
      getActionButton(new QPushButton(tr("Get Action"))),
      statusLabel(new QLabel(tr("Enter the server name "
                                "to join a game."))),
      socket(new QLocalSocket(this))
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QLabel *hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostLineEdit);

    statusLabel->setWordWrap(true);

    getActionButton->setDefault(true);
    QPushButton *quitButton = new QPushButton(tr("Quit"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getActionButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_10);

    connect(hostLineEdit, &QLineEdit::textChanged,
            this, &Client::enableGetActionButton);
    connect(getActionButton, &QPushButton::clicked,
            this, &Client::requestNewAction);
    connect(quitButton, &QPushButton::clicked, this, &Client::close);
    connect(socket, &QLocalSocket::readyRead, this, &Client::readAction);
    connect(socket, &QLocalSocket::errorOccurred, this, &Client::displayError);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    hostLineEdit->setFocus();
}

void Client::requestNewAction()
{
    getActionButton->setEnabled(false);
    blockSize = 0;
    socket->abort();
    socket->connectToServer(hostLineEdit->text());
}

void Client::readAction()
{
    if (blockSize == 0) {
        // Relies on the fact that QDataStream serializes a quint32 into
        // sizeof(quint32) bytes
        if (socket->bytesAvailable() < (int)sizeof(quint32))
            return;
        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize || in.atEnd())
        return;

    QString nextAction;
    in >> nextAction;

    if (nextAction == currentAction) {
        QTimer::singleShot(0, this, &Client::requestNewAction);
        return;
    }

    currentAction = nextAction;
    statusLabel->setText(currentAction);
    getActionButton->setEnabled(true);
}

void Client::displayError(QLocalSocket::LocalSocketError socketError)
{
    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:
        QMessageBox::information(this, tr("Operation H Client"),
                                 tr("The host was not found. Please make sure "
                                    "that the server is running and that the "
                                    "server name is correct."));
        break;
    case QLocalSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Operation H Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the server name "
                                    "is correct."));
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        QMessageBox::information(this, tr("Local Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(socket->errorString()));
    }

    getActionButton->setEnabled(true);
}

void Client::enableGetActionButton()
{
    getActionButton->setEnabled(!hostLineEdit->text().isEmpty());
}
