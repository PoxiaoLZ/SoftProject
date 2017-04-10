#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#include <QTime>
#include <map>

class Aircondition
{
private:
    bool Mode;
    bool Power;
    double DefaultTemperature;
    double MaxTemperature;
    double MinTemperature;
    QTime CurrentTime;
    map<int, RoomState> rooms;

public:
    Aircondition();
};

#endif // AIRCONDITION_H
