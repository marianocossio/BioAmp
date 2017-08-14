#include "acquisitionserverqt.h"

AcquisitionServerQt::AcquisitionServerQt()
{
    connect(&thread,SIGNAL(dataReceived(unsigned char)),this,SLOT(dataReceivedSignalReceived(unsigned char)));
    connect(&thread,SIGNAL(portOpened()),this,SLOT(portOpenedSignalReceived()));
    connect(&thread,SIGNAL(portClosed()),this,SLOT(portClosedSignalReceived()));
}

AcquisitionServerQt::~AcquisitionServerQt()
{

}

bool AcquisitionServerQt::startPort(QString portName)
{
    return thread.startPort(portName);
}

void AcquisitionServerQt::stopPort()
{
    thread.stopPort();
}

void AcquisitionServerQt::write(QByteArray data)
{
    thread.write(data);
}

void AcquisitionServerQt::setBaudRate(long baudRate)
{
    thread.setBaudRate(baudRate);
}

void AcquisitionServerQt::dataReceivedSignalReceived(unsigned char data)
{
    emit dataReceived(data);
}

void AcquisitionServerQt::portOpenedSignalReceived()
{
    emit portOpened();
}

void AcquisitionServerQt::portClosedSignalReceived()
{
    emit portClosed();
}
