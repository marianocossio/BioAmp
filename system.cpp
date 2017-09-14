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
    connect(&delayGenerator, SIGNAL(timeout()), this, SLOT(updateChannelsSlot()));
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

void System::updateChannels()
{
    delay(50);

    delayGenerator.start(50);
}

void System::activateChannel(int channel, bool activated)
{
    if (activated)
    {
        acquisitionServer.activateChannel(channel);
        acquisitionServer.write(activateChannelsCommands.mid(channel, 1));
        qDebug(activateChannelsCommands.mid(channel, 1));
    }

    else
    {
        acquisitionServer.deactivateChannel(channel);
        acquisitionServer.write(deactivateChannelsCommands.mid(channel, 1));
        qDebug(deactivateChannelsCommands.mid(channel, 1));
    }
}

void System::activateAllChannels()
{
    acquisitionServer.activateAllChannels();

    if (cascadeMode)
        acquisitionServer.write(activateChannelsCommands);

    else
        acquisitionServer.write(activateChannelsCommands.mid(0, 8));

    qDebug(activateChannelsCommands.mid(0, 8));
}

void System::deactivateAllChannels()
{
    acquisitionServer.deactivateAllChannels();

    if (cascadeMode)
        acquisitionServer.write(deactivateChannelsCommands);

    else
        acquisitionServer.write(deactivateChannelsCommands.mid(0, 8));

    qDebug(deactivateChannelsCommands.mid(0, 8));
}

void System::setTestSignal(int signal)
{
    acquisitionServer.write(testSignalCommands.mid(signal, 1));
    qDebug(testSignalCommands.mid(signal, 1));
}

void System::setChannelConnectionType(int channel, int type)
{
    channelConfigurationCommands[channel][4] = QByteArray::number(type)[0];
    acquisitionServer.write(channelConfigurationCommands[channel]);
    qDebug(channelConfigurationCommands[channel]);
}

void System::setChannelGain(int channel, int gain)
{
    channelConfigurationCommands[channel][3] = QByteArray::number(gain)[0];
    acquisitionServer.write(channelConfigurationCommands[channel]);
    qDebug(channelConfigurationCommands[channel]);
}

void System::setSampleRate(int sampleRate)
{
    acquisitionServer.write(sampleRateCommands.mid(sampleRate, 1));
    qDebug(sampleRateCommands.mid(sampleRate, 1));
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

void System::updateChannelsSlot()
{
    int channelsQuatity;
    acquisitionServer.write(channelConfigurationCommands[channelCommandIndex]);

    if (cascadeMode)
        channelsQuatity = 16;

    else
        channelsQuatity = 8;

    if ((++channelCommandIndex) >= channelsQuatity)
    {
        delayGenerator.stop();
        channelCommandIndex = 0;
    }
}

void System::delay(int msec)
{
    QTime chronometer;
    chronometer.start();

    while (chronometer.elapsed() < msec);
}
