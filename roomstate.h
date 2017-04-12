#ifndef ROOMSTATE_H
#define ROOMSTATE_H


class RoomState
{
private:

    int RoomNo;
    bool IsEmpty;
    bool Power;

    double RoomsTemperature;
    double TargetTemperature;
    double CurrentTemperature;

    int WindRate;

    double TotalCost;

    bool CurrentState;

public:
    RoomState();

    //set function
    void SetRoomNo(int _RoomNo);

    void SetIsEmpty(bool _IsEmpty);

    void SetPower(bool _Power);

    void SetTargetTemperature(int _TargetTemperature);

    void SetCurrentTemperature(int _CurrentTemperature);

    void SetWindRate(int _WindRate);

    void SetTotalCost(double _TotalCost);

    void SetCurrentState(bool CurrentState);

    //get function
    int GetRoomNo();

    bool GetIsEmpty();

    double GetTargetTemperature();

    double GetCurrentTemperature();

    int GetWindRate();

    double GetTotalCost();

    bool GetCurrentState();
};

#endif // ROOMSTATE_H
