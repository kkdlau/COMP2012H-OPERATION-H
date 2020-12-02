#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QDialog>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
QT_END_NAMESPACE

//! [0]
class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

private slots:
    void request_game_stat();
    void read_game_stat();
    void displayError(QAbstractSocket::SocketError socketError);
    void enable_get_game_stat_button();

private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *get_game_stat_Button = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream input;
    QString current_game_stat;
};
//! [0]

#endif

//#ifndef CLIENT_H
//#define CLIENT_H

//#include <QDialog>
//#include <QDataStream>
//#include <QLocalSocket>

//QT_BEGIN_NAMESPACE
//class QLabel;
//class QLineEdit;
//class QPushButton;
//QT_END_NAMESPACE

//class Client : public QDialog
//{
//    Q_OBJECT

//public:
//    explicit Client(QWidget *parent = nullptr);

//private slots:
//    void requestNewAction();
//    void readAction();
//    void displayError(QLocalSocket::LocalSocketError socketError);
//    void enableGetActionButton();

//private:
//    QLineEdit *hostLineEdit;
//    QPushButton *getActionButton;
//    QLabel *statusLabel;

//    QLocalSocket *socket;
//    QDataStream in;
//    quint32 blockSize;

//    QString currentAction;
//};

//#endif // CLIENT_H
