#include "healthbar.h"
#include "qbrush.h"

HealthBar::HealthBar(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0,0,40,5);
    setBrush(QBrush(Qt::red));
    setRotation(90);
}

void HealthBar::UpdateBar()
{
    double healthRange = 80 * (currentValue / maximumValue);
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
