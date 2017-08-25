#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    bufferSize = 256;

    connect(&acquisitionServer, SIGNAL(dataReady(DataSet)), this, SLOT(receiveData(DataSet)));
}

System::~System()
{
    acquisitionServer.stopPort();
}

bool System::start(QString portName, int baudRate)
{
    acquisitionServer.setBaudRate(baudRate);
    bool result = acquisitionServer.startPort(portName);

    if (result)
        graph.show();

    return result;
}

void System::stop()
{
    acquisitionServer.stopPort();
    graph.close();
}

bool System::receivingData()
{
    return acquisitionServer.portIsActive();
}

void System::send(QByteArray data)
{
    acquisitionServer.write(data);
}

QList<QString> System::availablePorts()
{
    return acquisitionServer.availablePorts();
}

void System::activateChannel(int channel)
{
    acquisitionServer.activateChannel(channel);
}

void System::deactivateChannel(int channel)
{
    acquisitionServer.deactivateChannel(channel);
}

void System::activateAllChannels()
{
    acquisitionServer.activateAllChannels();
}

void System::deactivateAllChannels()
{
    acquisitionServer.deactivateAllChannels();
}

void System::receiveData(DataSet data)
{
    if (buffer.size() >= bufferSize)
    {
        buffer.clear();
    }

    graph.addData(data);

    buffer.push_back(data);
}
