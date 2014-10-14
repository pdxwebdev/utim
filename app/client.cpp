// client.cpp

#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::doConnect()
{
    socket = new QTcpSocket(this);

    //connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    //connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    //connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    //connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("localhost", 8901);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    } else {
        qDebug() << "connected blocking...";
        socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(30000);
        qDebug() << "reading blocking..." << socket->bytesAvailable();
        qDebug() << socket->readAll();
        socket->close();
    }
}

void Client::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
    qDebug() << "done writing...";
    
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();

}

void Client::disconnected()
{
    qDebug() << "disconnected...";
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}
