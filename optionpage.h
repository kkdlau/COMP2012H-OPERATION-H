#ifndef OPTIONPAGE_H
#define OPTIONPAGE_H

#include <QDialog>

namespace Ui {
class OptionPage;
}

class OptionPage : public QDialog
{
    Q_OBJECT

public:
    explicit OptionPage(QWidget *parent = nullptr);
    ~OptionPage();
    void passFromMain(int*, int*, int*);

private slots:
    void on_numMeleeSlider_sliderMoved(int position);

    void on_numRangedSlider_sliderMoved(int position);

    void on_bulletSpeedSlider_sliderMoved(int position);

private:
    Ui::OptionPage *ui;
    int* numMelee;
    int* numRanged;
    int* bulletSpeed;
};

#endif // OPTIONPAGE_H
