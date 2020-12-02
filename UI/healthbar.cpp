#include "healthbar.h"
#include "qbrush.h"

HealthBar::HealthBar(QGraphicsItem *parent, int initialHealth, int totalHealth) : QGraphicsRectItem(parent)
{
    setRect(-20,30,40,5);
    setBrush(QBrush(Qt::red));
    setRotation(90);
    SetValue(initialHealth, totalHealth);
}

void HealthBar::UpdateBar()
{
    double healthRange = 40 * (currentValue / maximumValue);
    setRect(rect().x(),rect().y(),healthRange,5);
}

void HealthBar::IncrementBar(float amount)
{
    currentValue += amount;
    UpdateBar();
}

void HealthBar::DecrementBar(float amount)
{
    currentValue -= amount;
    UpdateBar();
}

void HealthBar::SetValue(int currentValue, int maximumValue)
{
    this->currentValue = currentValue;
    this->maximumValue = maximumValue;
}
