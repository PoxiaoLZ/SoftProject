#include "aircondition.h"

Aircondition::Aircondition()
{
	init();
    Timer = new QTimer;
    Timer->start(TimeRadio);
    connect(Timer, SIGNAL(timeout()), this, RealTimeControl());
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

    TcpServer = new QTcpServer(this);
    TcpSocket = new QTcpSocket(this);
    TcpServer->listen(QHostAddress::Any,PORT);//监听的端口号
    connect(m_tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

void Aircondition::newConnect()
{
    TcpSocket = TcpServer->nextPendingConnection();//设置监听
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(ReceiveMessage())); //服务器接收客户端的消息
    //connect(TcpSocket,SIGNAL(disconnected()),TcpSocket,SLOT(deleteLater()));
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
    QDataStream out(&Message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << quint8(Type) << IsComfirmed;
    out.device()->seek(0);
    out << quint16(Message.size() - sizeof(quint16));
    SocketList[RoomNo]->write(Message);
}

void Aircondition::SendMessage(int RoomNo, char Type)
{
    QDataStream out(&Message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << quint8(Type);
    out.device()->seek(0);
    out << quint16(Message.size() - sizeof(quint16));
    SocketList[RoomNo]->write(Message);
}

void Aircondition::SendMessage(int RoomNo, char Type, double value)
{
    QDataStream out(&Message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << quint8(Type) << value;
    out.device()->seek(0);
    out << quint16(Message.size() - sizeof(quint16));
    SocketList[RoomNo]->write(Message);
}

void Aircondition::SendMessage(int RoomNo, char Type, bool mode, double value1, double value2, double Temp, int Level)
{
    QDataStream out(&Message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << quint8(Type) << mode << value1 << value2 << Temp << Level;
    out.device()->seek(0);
    out << quint16(Message.size() - sizeof(quint16));
    SocketList[RoomNo]->write(Message);
}

void Aircondition::ReceiveMessage()
{
    QDataStream input(TcpSocket);
    quint16 length;
    quint8 value;
    int RoomNo;
    double Temperature,RoomTemperature;
    int Level;
    input >> length >> value;
    switch(value)
    {
    case 'I':
        input >> RoomNo >> RoomTemperature;
        if(SocketList.contains(RoomNo))
        {
            QDataStream out(&Message,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_5);
            out << quint16(0) << quint8('I') << false;
            out.device()->seek(0);
            out << quint16(Message.size() - sizeof(quint16));
            TcpSocket->write(Message);
        }
        else
        {
            SocketList.insert(RoomNo,TcpSocket);
            QDataStream out(&Message,QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_5);
            out << quint16(0) << quint8('I') << true;
            out.device()->seek(0);
            out << quint16(Message.size() - sizeof(quint16));
            TcpSocket->write(Message);
            rooms[RoomNo].SetRoomsTemperature(RoomTemperature);
        }
        break;
    case 'B':
        input >> RoomNo;
        rooms[RoomNo].SetPower(true);
        AddRequest(rooms[RoomNo]);
        break;
    case 'E':
        input >> RoomNo;
        rooms[RoomNo].SetPower(false);
        AddRequest(rooms[RoomNo]);
        break;
    case 'Q':
        input >> RoomNo;
        SocketList.remove(RoomNo);
        break;
    case 'T':
        input >> RoomNo >> Temperature;
        rooms[RoomNo].SetTargetTemperature(Temperature);
        AddRequest(rooms[RoomNo]);
        SendMessage(RoomNo,'H',!rooms[RoomNo].GetCurrentState());
        break;
    case 'R':
        input >> RoomNo >> Level;
        rooms[RoomNo].SetWindRate(Level);
        AddRequest(rooms[RoomNo]);
        SendMessage(RoomNo,'H',!rooms[RoomNo].GetCurrentState());
        break;
    case 'G':
        input >> RoomNo;
        AddRequest(rooms[RoomNo]);
        SendMessage(RoomNo,'H',!rooms[RoomNo].GetCurrentState());
        break;
    case 'C':
        input >> RoomNo >> Temperature;
        rooms[RoomNo].SetCurrentTemperature(Temperature);
        break;
    }
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


void Aircondition::TempChange(int RoomNo)
{
    double delta = abs(rooms[RoomNo].GetCurrentTemperature() - rooms[RoomNo].GetRoomsTemperature());//当前温差

    if(!rooms[RoomNo].GetPower() || !rooms[RoomNo].GetCurrentState())//空调关或者被挂起，什么都不干
        continue;
    else if(Mode && rooms[RoomNo].GetCurrentTemperature() <= rooms[RoomNo].GetTargetTemperature()){
        //制冷并且当前温度低于目标温度
        rooms[RoomNo].SetCurrentState(false);//空调挂起
        SendMessage(RoomNo, 'H', true);
    }
    else if(!Mode && rooms[RoomNo].GetCurrentTemperature() >= rooms[RoomNo].GetTargetTemperature()){
        //制热并且当前温度高于目标温度
        rooms[RoomNo].SetCurrentState(false);//空调挂起
        SendMessage(RoomNo, 'H', true);
    }
    else if(Mode){//制冷
        double delta2 = abs(rooms[RoomNo].GetCurrentTemperature() - rooms[RoomNo].GetTargetTemperature());
        if(rooms[RoomNo].GetWindRate() == 1){
            if(delta2 >= 0.5)
                rooms[RoomNo].SubTemp(0.5);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
        else if(rooms[RoomNo].GetWindRate() == 2){
            if(delta2 >= 0.75)
                rooms[RoomNo].SubTemp(0.75);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
        else if(rooms[RoomNo].GetWindRate() == 3){
            if(delta2 >= 1.0)
                rooms[RoomNo].SubTemp(1.0);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
    }
    else if(!Mode){//制热
        double delta2 = abs(rooms[RoomNo].GetCurrentTemperature() - rooms[RoomNo].GetTargetTemperature());
        if(rooms[RoomNo].GetWindRate() == 1){
            if(delta2 >= 0.5)
                rooms[RoomNo].AddTemp(0.5);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
        else if(rooms[RoomNo].GetWindRate() == 2){
            if(delta2 >= 0.75)
                rooms[RoomNo].AddTemp(0.75);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
        else if(rooms[RoomNo].GetWindRate() == 3){
            if(delta2 >= 1.0)
                rooms[RoomNo].AddTemp(1.0);
            else{
                rooms[RoomNo].SetCurrentTemperature(rooms[RoomNo].GetTargetTemperature());
                rooms[RoomNo].SetCurrentState(false);//挂起
                SendMessage(RoomNo, 'A');
            }
        }
    }
}

void Aircondition::RealTimeControl()
{
    for(int i = 1; i <= 4; i++){
        if(rooms[i].GetIsEmpty())
            continue;
        TempChange(i);
        SendMessage(rooms[i].GetRoomNo(), 'C', rooms[i].GetCurrentTemperature());
    }

    /*
    *if(需要调度)
    *    调度
    */
}
