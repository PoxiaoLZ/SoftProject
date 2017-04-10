#ifndef ROOMSTATE_H
#define ROOMSTATE_H


class RoomState
{
private:
    int RoomNo;
    double TargetTemperature;
    double CurrentTemperature;
    int WindRate;
    double TotalCost;
    bool CurrentState;


public:
    RoomState();
};

#endif // ROOMSTATE_H
