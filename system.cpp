#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    bufferSize = 256;

    cascadeMode = false;
    channelCommandIndex = 0;

    activateChannelsCommands   = "!@#$%^&*QWERTYUI";
    deactivateChannelsCommands = "12345678qwertyui";
    testSignalCommands = "0-=p[]";
    sampleRateCommands = "ASFG";

    channelConfigurationCommands.push_back("x1060110X");
    channelConfigurationCommands.push_back("x2060110X");
    channelConfigurationCommands.push_back("x3060110X");
    channelConfigurationCommands.push_back("x4060110X");
    channelConfigurationCommands.push_back("x5060110X");
    channelConfigurationCommands.push_back("x6060110X");
    channelConfigurationCommands.push_back("x7060110X");
    channelConfigurationCommands.push_back("x8060110X");
    channelConfigurationCommands.push_back("x9060110X");
    channelConfigurationCommands.push_back("x:060110X");
    channelConfigurationCommands.push_back("x;060110X");
    channelConfigurationCommands.push_back("x<060110X");
    channelConfigurationCommands.push_back("x=060110X");
    channelConfigurationCommands.push_back("x>060110X");
    channelConfigurationCommands.push_back("x?060110X");
    channelConfigurationCommands.push_back("x@060110X");

    connect(&acquisitionServer, SIGNAL(dataReady(DataSet)), this, SLOT(receiveData(DataSet)));
    connect(&ticker, SIGNAL(timeout()), this, SLOT(sendCommands()));
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
    {
        graph.show();
        acquisitionServer.write("b");
        qDebug("b");
    }

    return result;
}

void System::stop()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.write("s");
        qDebug("s");
        acquisitionServer.stopPort();
    }
    graph.close();
}

bool System::receivingData()
{
    return acquisitionServer.portIsActive();
}

void System::send(QByteArray data)
{
    acquisitionServer.write(data);
    qDebug(data);
}

QList<QString> System::availablePorts()
{
    return acquisitionServer.availablePorts();
}

void System::flush()
{
    if (!ticker.isActive())
        ticker.start(50);
}

void System::activateChannel(int channel, bool activated)
{
    if (activated)
    {
        acquisitionServer.activateChannel(channel);
        commandsBuffer.push_back(activateChannelsCommands.mid(channel, 1));
    }

    else
    {
        acquisitionServer.deactivateChannel(channel);
        commandsBuffer.push_back(deactivateChannelsCommands.mid(channel, 1));
    }
}

void System::activateAllChannels()
{
    acquisitionServer.activateAllChannels();

    if (cascadeMode)
        commandsBuffer.push_back(activateChannelsCommands);

    else
        commandsBuffer.push_back(activateChannelsCommands.mid(0, 8));
}

void System::deactivateAllChannels()
{
    acquisitionServer.deactivateAllChannels();

    if (cascadeMode)
        commandsBuffer.push_back(deactivateChannelsCommands);

    else
        commandsBuffer.push_back(deactivateChannelsCommands.mid(0, 8));
}

void System::setTestSignal(int signal)
{
    commandsBuffer.push_back(testSignalCommands.mid(signal, 1));
}

void System::setChannelConnectionType(int channel, int type)
{
    channelConfigurationCommands[channel][4] = QByteArray::number(type)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setChannelGain(int channel, int gain)
{
    channelConfigurationCommands[channel][3] = QByteArray::number(gain)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setSampleRate(int sampleRate)
{
    commandsBuffer.push_back(sampleRateCommands.mid(sampleRate, 1));
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

void System::sendCommands()
{
    if (commandsBuffer.size() > 0)
    {
        acquisitionServer.write(commandsBuffer[0]);
        //qDebug(commandsBuffer[0]);
        commandsBuffer.pop_front();

        if (commandsBuffer.size() == 0)
            ticker.stop();
    }
}
