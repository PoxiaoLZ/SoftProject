#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QString>
#include <map>
#include "roomstate.h"
#include "mainwindow.h"
#include "bill.h"
using namespace std;

class Aircondition
{
private:
    bool Mode;
    bool Power;
    double DefaultTemperature;
    double MaxTemperature;
    double MinTemperature;
    double HighCost;
    double MiddleCost;
    double SendFrequency;
    int TimeRadio;
    QTime CurrentTime;
    //map<int, RoomState> rooms;
    RoomState rooms[21];

private:
    MainWindow *ui;

private:
    map<int, QTcpSocket*> TcpSockets;

    QTcpServer *TcpServer;

public:
    Aircondition();

    void init(); //initialize the state of aircondition

    Bill* PrintBill(void);

    double CalculateCost(void);

    void TempChange(int RoomNo);

    void TemperatureChange(int RoomNo, double Temperature); //change rooms' temperatures(server -> client)

    void WindChange(int RoomNo, int Level); //change rooms' wind level(server -> client)

    void ChangeTargetTemp(int RoomNo, double Temperature); //change rooms' temperatures(client -> server)

    void ChangeTargetWind(int RoomNo, int Level); //change rooms' wind level(client -> server)

    void ConfirmConnected(int RoomNo); //ȷ�ϸ÷�����Ƿ�����ã�������ack

    void CancelConnected(int RoomNo);

    void RoomPowerOn(int RoomNo); //�յ�����յ�������������server�˷���״̬������ȴ�����

    void RoomPowerOff(int RoomNo); //�յ�����ػ�����

private:
    void SendMessage(int RoomNo, char Type, bool IsConfirmed); //send I or H or P

    void SendMessage(int RoomNo, char Type, double value); //send C or O

private slots:
    /*telecommunication functions*/
    void ReceiveMessage(); // receive all messeges and determine the type

    void NewListen(); //setup new connection

    void AcceptConnection(); //Accept the connection from client

    void ShowError(QAbstractSocket::SocketError); //error output tips. perhaps it can be delete

    void PowerOn(void);

    void PowerOff(void);
};

#endif // AIRCONDITION_H
