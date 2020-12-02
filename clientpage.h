#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QDialog>
#include "Network/tcpclient.h"
namespace Ui {
class ClientPage;
}

class ClientPage : public QDialog
{
    Q_OBJECT

public:
    explicit ClientPage(QWidget *parent = nullptr);
    void display_error(QAbstractSocket::SocketError socketError);
    ~ClientPage();

public slots:
    void debug_connected();
    void debug_disconnected();
private slots:
    void on_pushButton_clicked();

private:
    Ui::ClientPage *ui;
};

#endif // CLIENTPAGE_H
