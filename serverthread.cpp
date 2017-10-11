#include "serverthread.h"

ServerThread::ServerThread(QObject *parent) : QThread(parent)
{
    abort = false;

    baudRate = 115200;

    connectionAttempts = 0;

    connect(&portBioAmp, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(&portBioAmp, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(errorOccurredReceived()));
}

ServerThread::~ServerThread()
{
    mutex.lock();

    abort = true;
    condition.wakeOne();

    mutex.unlock();

    wait();
}

bool ServerThread::startPort(QString portName)
{
    bool result;

    QMutexLocker locker(&mutex);

    portBioAmp.setPortName(portName);
    portBioAmp.setBaudRate(baudRate);
    portBioAmp.open(QSerialPort::ReadWrite);

    result = portBioAmp.isOpen();

    if (!isRunning())
        start(LowPriority);
    else
        condition.wakeOne();

    if (result)
    {
        abort = false;

        connectionAttempts = 10;

        emit portOpened();
    }

    else
        emit connectionError();

    return result;
}

void ServerThread::stopPort()
{
    connectionAttempts = 0;

    mutex.lock();

    if (portBioAmp.isOpen())
        portBioAmp.close();

    abort = true;
    condition.wakeOne();

    mutex.unlock();

    wait();

    emit portClosed();
}

bool ServerThread::portIsActive()
{
    return portBioAmp.isOpen();
}

void ServerThread::write(QByteArray data)
{
    mutex.lock();

    portBioAmp.write(data);

    mutex.unlock();
}

QList<QString> ServerThread::availablePorts()
{
    QList<QString> availablePortNames;

    for (int index = 0; index < QSerialPortInfo::availablePorts().size(); index++)
        availablePortNames.push_back(QSerialPortInfo::availablePorts()[index].portName());

    return availablePortNames;
}

void ServerThread::setBaudRate(long baudRate)
{
    this->baudRate = baudRate;

    if (portBioAmp.isOpen())
    {
        portBioAmp.close();

        startPort(portBioAmp.portName());
    }
}

void ServerThread::run()
{
    forever
    {
        if (abort)
            return;
    }
}

void ServerThread::readData()
{
    int bytesAvailable;

    mutex.lock();

    bytesAvailable = portBioAmp.bytesAvailable();

    mutex.unlock();

    if (bytesAvailable)
    {
        QByteArray receivedBytes;

        mutex.lock();

        receivedBytes.append(portBioAmp.read(bytesAvailable));

        mutex.unlock();

        if (receivedBytes.size() > 0)
            emit dataReceived(receivedBytes);
    }
}

void ServerThread::errorOccurredReceived()
{
    if (connectionAttempts < 10)
        connectionAttempts++;

    else
    {
        connectionAttempts = 0;

        emit connectionError();
    }
}
