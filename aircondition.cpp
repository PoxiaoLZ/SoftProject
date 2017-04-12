#include "aircondition.h"

Aircondition::Aircondition()
{
	init();
}

void Aircondition::init()
{
	
	for(int i = 1; i <= 20; i ++)
		rooms[i] = new RoomState(/*here need to insert some attribute*/);
	
	//the operations below are to set the first temperature of the rooms
	rooms[1].SetCurrentTemperature(30);
	rooms[2].SetCurrentTemperature(30);
	rooms[3].SetCurrentTemperature(30);
	rooms[4].SetCurrentTemperature(30);
}

Bill* Aircondition::PrintBill(void)
{
	BillPrint = new Bill();
	BillPrint.set()
}

double Aircondition::CalculateCost(void)
{
	/*map<int, RoomState>::iterator iter;
	for(iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		
	}*/
	for(int i = 1; i <= 20; i++)
	{
		
	}
}



void Aircondition::WindChange(int RoomNo, int Level)
{
	rooms[RoomNo].SetWindRate(Level);
}

void Aircondition::ChangeTargetTemp(int RoomNo, double Temperature)
{
	rooms[RoomNo].SetTargetTemperature(Temperature);
}

void Aircondition::ChangeTargetWind(int RoomNo, int Level)
{
	rooms[RoomNo].SetWindRate(Level);
}

void Aircondition::ConfirmConnected(int RoomNo)
{
	if(rooms.GetIsEmpty())
	{
		//send ack
	}
	else 
	{
		//send nak
	}
}

void Aircondition::RoomPowerOn(int RoomNo)
{
	rooms[RoomNo].SetPower(true);
	rooms[RoomNo].SetTargetTemperature(DefaultTemperature);
}

void Aircondition::RoomPowerOff(int RoomNo)
{
	rooms[RoomNo].SetPower(false);
	//call temperature change function
}

void Aircondition::SendMessage(int RoomNo, char Type, bool IsComfirmed)
{
	
}

void Aircondition::SendMessage(int RoomNo, char Type, double value)
{
	
}

void Aircondition::ReceiveMessage()
{
	
}

void Aircondition::NewListen()
{
	
}

void Aircondition::AcceptConnection()
{
	
}

void Aircondition::ShowError(QAbstractSocket::SocketError)
{
	
}


