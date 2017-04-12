#include "aircondition.h"

Aircondition::Aircondition()
{

}

void Aircondition::init()
{

}

void Aircondition::TempChange(int RoomNo)
{
    if(rooms[RoomNo].CurrentState){
        if(Mode == true && rooms[RoomNo].CurrentTemperature <= rooms[RoomNo].TargetTemperature)
            rooms[RoomNo].CurrentState = false;
        else if(Mode == false && rooms[RoomNo].CurrentTemperature >= rooms[RoomNo].TargetTemperature)
            rooms[RoomNo].CurrentState = false;
        else if(rooms[RoomNo].WindRate == 1){

        }
        else if(rooms[RoomNo].WindRate == 2){

        }
        else if(rooms[RoomNo].WindRate == 3){

        }
    }
    else{

    }
}
