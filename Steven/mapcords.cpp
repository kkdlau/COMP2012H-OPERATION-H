#include "mapcords.h"

MapCords::MapCords(int x, int y):x(x), y(y){};
//accessor
bool MapCords::cord_valid() const
{
    return x >= 0 && y >= 0;
}
int MapCords::get_x() const
{
    return x;
}
int MapCords::get_y() const
{
    return y;
}
