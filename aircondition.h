#ifndef AIRCONDITION_H
#define AIRCONDITION_H
#define PORT 3500
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QString>
#include <qmap>
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
    int TimeRadio; //1min = ��sec
    QTime CurrentTime;
    QTimer *Timer;

//    map<int, RoomState> rooms;
    RoomState rooms[21];

private:
    MainWindow *ui;

private:
    QMap<int, QTcpSocket*> SocketList;
    QByteArray Message;
    QTcpServer *TcpServer;
    QTcpSocket *TcpSocket;

public:
    Aircondition();

    void newConnect();

    void init(); //initialize the state of aircondition

    Bill* PrintBill(void);

    double CalculateCost(void);

    void TempChange(int RoomNo); //ʵʱ���е��¶ȱ仯

    void TemperatureChange(int RoomNo, double Temperature); //change rooms' temperatures(server -> client)

    void WindChange(int RoomNo, int Level); //change rooms' wind level(server -> client)

    void ChangeTargetTemp(int RoomNo, double Temperature); //change rooms' temperatures(client -> server)

    void ChangeTargetWind(int RoomNo, int Level); //change rooms' wind level(client -> server)

    void ConfirmConnected(int RoomNo); //ȷ�ϸ÷�����Ƿ�����ã�������ack

    void CancelConnected(int RoomNo); //�˷�

    void RoomPowerOn(int RoomNo); //�յ�����յ�������������server�˷���״̬������ȴ�����

    void RoomPowerOff(int RoomNo); //�յ�����ػ�����

    void TempChange(int RoomNo);

private:
    void SendMessage(int RoomNo, char Type); // send 'A'

    void SendMessage(int RoomNo, char Type, bool IsConfirmed); //send I or H

    void SendMessage(int RoomNo, char Type, bool mode, double value1, double value2, double Temp, int Level); //send P

    void SendMessage(int RoomNo, char Type, double value); //send C or O

private slots:
    void ReceiveMessage(); // receive all messeges and determine the type

    void NewListen(); //setup new connection

    void AcceptConnection(); //Accept the connection from client

    void ShowError(QAbstractSocket::SocketError); //error output tips. perhaps it can be delete

    void PowerOn(void);

    void PowerOff(void);

    void RealTimeControl();
};

#endif // AIRCONDITION_H
