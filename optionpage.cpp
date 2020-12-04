#include "optionpage.h"
#include "ui_optionpage.h"
#include <QDebug>

OptionPage::OptionPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionPage)
{
    ui->setupUi(this);
}

OptionPage::~OptionPage()
{
    delete ui;
}

void OptionPage::passFromMain(int* inputMelee, int* inputRanged, int* inputbulletSpeed) {
    this->numMelee = inputMelee;
    this->numRanged = inputRanged;
    this->bulletSpeed = inputbulletSpeed;
    ui->numMeleeSlider->setSliderPosition(*numMelee);
    ui->numRangedSlider->setSliderPosition(*numRanged);
}


void OptionPage::on_numMeleeSlider_sliderMoved(int position)
{
    qDebug() << "Number of melee now: "<< position;
    *numMelee = position;
}

void OptionPage::on_numRangedSlider_sliderMoved(int position)
{
    qDebug() << "Number of ranged now: "<< position;
    *numRanged = position;
}

void OptionPage::on_bulletSpeedSlider_sliderMoved(int position)
{
    qDebug() << "Bullet speed now: "<< position;
    *bulletSpeed = position;
}
