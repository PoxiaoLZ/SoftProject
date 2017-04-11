#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <map>
#include "roomstate.h"
#include "mainwindow.h"
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
    map<int, RoomState> rooms;

private:
    MainWindow *ui;

private:
    QTcpSocket *TcpSocket;
    QTcpServer *TcpServer;

public:
    Aircondition();

    void init(); //initialize the state of aircondition

    void PowerOn(); //receive a request
    void PowerOff(); //receive a request

    Bill* PrintBill(void);

    double CalculateCost(void);

    void TemperatureChange(); //send a message
    void ChangeTargetState(); //receive a request

private:
    //telecommunication function
    void SendMessage();
    void ReceiveMessage();
    void NewListen(); //setup new connection
    void AcceptConnection(); //Accept the connection from client
    void ShowError(QAbstractSocket::SocketError); //error output tips. perhaps it can be delete
};

#endif // AIRCONDITION_H
