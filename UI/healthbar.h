#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "QGraphicsRectItem"

class HealthBar: public QGraphicsRectItem
{
public:
    HealthBar(QGraphicsItem * parent,int initialHealth = 1,int MaxHealth = 1);
    void UpdateBar();
    void IncrementBar(float amount);
    void DecrementBar(float amount);
    void SetValue(int currentValue, int maximumValue);
private:
    float currentValue = 1;
    float maximumValue = 1;
};

#endif // HEALTHBAR_H
