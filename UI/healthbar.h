#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "QGraphicsRectItem"

class HealthBar: public QGraphicsRectItem
{
public:
    HealthBar(QGraphicsItem * parent);
    void UpdateBar();
    void IncrementBar(float amount);
    void DecrementBar(float amount);
private:
    float currentValue = 1;
    float maximumValue = 1;
};

#endif // HEALTHBAR_H
