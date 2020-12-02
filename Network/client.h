#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QDataStream>
#include <QLocalSocket>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

private slots:
    void requestNewAction();
    void readAction();
    void displayError(QLocalSocket::LocalSocketError socketError);
    void enableGetActionButton();

private:
    QLineEdit *hostLineEdit;
    QPushButton *getActionButton;
    QLabel *statusLabel;

    QLocalSocket *socket;
    QDataStream in;
    quint32 blockSize;

    QString currentAction;
};

#endif // CLIENT_H
