#include "system.h"

System::System(QObject *parent) : QObject(parent)
{
    bufferSize = 256;
    buffer.resize(bufferSize);

    cascadeMode = false;

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

    graph.setWindowTitle("BioAmp - Graphics");

    connect(&acquisitionServer, SIGNAL(dataReady(DataSet)), this, SLOT(receiveData(DataSet)));
    connect(&ticker, SIGNAL(timeout()), this, SLOT(sendCommands()));
    connect(&impedanceTicker, SIGNAL(timeout()), this, SLOT(getChannelImpedance()));
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
        acquisitionServer.write("b");

    return result;
}

void System::stop()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.write("s");

        acquisitionServer.stopPort();
    }

    if (graph.isVisible())
        graph.close();
}

void System::pause()
{
    if (acquisitionServer.portIsActive())
    {
        acquisitionServer.write("s");

        acquisitionServer.stopPort();
    }
}

bool System::receivingData()
{
    return acquisitionServer.portIsActive();
}

void System::send(QByteArray data)
{
    acquisitionServer.write(data);
    //qDebug(data);
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

void System::setChannelConnectionType(int channel, ConnectionType type)
{
    channelConfigurationCommands[channel][4] = QByteArray::number(type)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setChannelGain(int channel, int gain)
{
    channelConfigurationCommands[channel][3] = QByteArray::number(gain)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setChannelSRB2(int channel, bool set)
{
    channelConfigurationCommands[channel][6] = QByteArray::number(set)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::setSampleRate(int sampleRate)
{
    commandsBuffer.push_back(sampleRateCommands.mid(sampleRate, 1));
}

void System::toggleGraphVisibility()
{
    if (graph.isVisible())
        graph.hide();
    else
        graph.show();
}

void System::startCheckingChannelImpedance(int channel, System::ChannelTerminal terminal)
{
    switch (terminal)
    {
    case P_Terminal:
        commandsBuffer.push_back("z" + QByteArray::number(channel + 1) + "10Z");
        break;
    case N_Terminal:
        commandsBuffer.push_back("z" + QByteArray::number(channel + 1) + "01Z");
        break;
    default:
        break;
    }

    flush();

    impedanceTicker.start(500);

    channelCommandIndex = channel;
    channelCommandTerminal = terminal;
}

void System::stopCheckingChannelImpedance()
{
    impedanceTicker.stop();

    commandsBuffer.push_back("z" + QByteArray::number(channelCommandIndex + 1) + "00Z");
    commandsBuffer.push_back(channelConfigurationCommands[channelCommandIndex]);

    flush();
}

void System::connectToBIAS(int channel, bool connect)
{
    channelConfigurationCommands[channel][5] = QByteArray::number(connect)[0];
    commandsBuffer.push_back(channelConfigurationCommands[channel]);
}

void System::getChannelImpedance()
{
    if (channelCommandIndex < buffer[0].getDataType())
    {
        double rmsSum = 0;
        double rmsValue = 0;
        double impedance = 0;
        double DC = 0;

        for (unsigned index = 0; index < bufferSize; index++)
            DC += buffer[index].channelData(channelCommandIndex);

        DC = DC / (bufferSize * 1.0);

        for (unsigned index = 0; index < bufferSize; index++)
            rmsSum += ((((buffer[index].channelData(channelCommandIndex) - DC) / (SIGNAL_MAX_VALUE * 1.0)) * 4.5)
                       * (((buffer[index].channelData(channelCommandIndex) - DC) / (SIGNAL_MAX_VALUE * 1.0)) * 4.5));

        rmsValue = sqrt(rmsSum / (bufferSize * 1.0));

        impedance = rmsValue / (0.0006);

        emit impedanceCalculated(channelCommandIndex, channelCommandTerminal, impedance);
    }
}

void System::receiveData(DataSet data)
{
    buffer.pop_front();

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
