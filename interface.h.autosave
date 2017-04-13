#ifndef INTERFACE_H
#define INTERFACE_H 
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <qmap.h>
#define PORT 3500
using namespace std;

class interface
{
public:
    interface();
    void newConnect();
    void readMessage();
private:
    QTcpSocket *TcpSocket;
    QTcpServer *TcpServer;
    QByteArray Message;
    QMap<int,QTcpSocket*> SocketList;
};

#endif // INTERFACE_H
