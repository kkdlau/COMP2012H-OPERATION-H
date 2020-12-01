#ifndef HOSTPAGE_H
#define HOSTPAGE_H

#include <QDialog>
#include "Network/tcpserver.h"
namespace Ui {
class HostPage;
}

class HostPage : public QDialog
{
    Q_OBJECT

public:
    explicit HostPage(QWidget *parent = nullptr);
    ~HostPage();
    void update_ip();
private:
    Ui::HostPage *ui;
    QTcpServer* tcp_server;
};

#endif // HOSTPAGE_H
