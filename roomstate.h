#ifndef ROOMSTATE_H
#define ROOMSTATE_H


class RoomState
{
public:
    int RoomNo;
    bool IsEmpty;
    bool Power;

    double RoomsTemperature;
    double TargetTemperature;
    double CurrentTemperature;
    double TotalCost;

    int WindRate;
    bool CurrentState;

public:
    RoomState();
};

#endif // ROOMSTATE_H
