#ifndef MAPCORDS_H
#define MAPCORDS_H


class MapCords
{
public:
    MapCords(int, int);
    //accessor
    bool cord_valid() const;
    int get_x() const;
    int get_y() const;

private:
    int x = -1;
    int y = -1;
};

#endif // MAPCORDS_H
