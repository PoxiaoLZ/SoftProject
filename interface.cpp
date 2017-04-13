#include "interface.h"

interface::interface()
{
    TcpServer = new QTcpServer(this);
    TcpSocket = new QTcpSocket(this);
    TcpServer->listen(QHostAddress::Any,PORT);//监听的端口号
    connect(m_tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
}

void interface::newConnect()
{
    TcpSocket = TcpServer->nextPendingConnection();//设置监听
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage())); //服务器接收客户端的消息
    connect(TcpSocket,SIGNAL(disconnected()),TcpSocket,SLOT(deleteLater()));
}

void interface::readMessage()
{
    QDataStream input(TcpSocket);
    quint16 length;
    quint8 value;
    int RoomNo;
    input >> length >> value;
    switch(value)
    {
    case 'I':
        input >> RoomNo;
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
        }
        break;
    case 'B':
        input >> RoomNo;

        //改变当前温度
        break;
    case 'P':
        input >> State >> MinTemp >> MaxTemp;
        //改变工作模式，制冷/热，温度上下限
        break;
    case 'O':
        input >> Cost;
        //总费用
        break;
    case 'H':
        //挂起
        break;
    }
}
