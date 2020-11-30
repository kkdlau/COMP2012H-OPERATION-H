#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QDialog>

namespace Ui {
class NetworkPage;
}

class NetworkPage : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkPage(QWidget *parent = nullptr);
    ~NetworkPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NetworkPage *ui;
};

#endif // NETWORKPAGE_H
