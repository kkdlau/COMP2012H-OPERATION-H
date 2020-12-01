#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QDialog>

namespace Ui {
class ClientPage;
}

class ClientPage : public QDialog
{
    Q_OBJECT

public:
    explicit ClientPage(QWidget *parent = nullptr);
    ~ClientPage();
    void update_ip();
private:
    Ui::ClientPage *ui;
};

#endif // CLIENTPAGE_H
